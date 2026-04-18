#include "ExtensionsManager.h"

#define LOGGER_NAME "Extensions Manager"

#include <windows.h>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QMetaMethod>

#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QFile>
#include <QFileDevice>
#include <qthreadpool.h>

#include <QtCore/private/qobject_p.h>
#include <QtCore/private/qhooks_p.h>
#include <QtCore/private/qfiledevice_p.h>
#include <QtCore/qobjectdefs.h>

#include "ExtensionsSettings.h"

#include "HooksManager.h"
#include "MVCustomDoubleSpinBox.h"
#include "MVStatusBar.h"

static QObject *test;
static QObject *ap;

struct Hack : QObject {
    using QObject::receivers;
};

// ── UtilityAPIInterface::CreateProgressBar vtable hook ────────────────────────
// CLOAPIInterface.dll exports CreateProgressBar at RVA 0x00001860, a shared stub
// address (189 other methods resolve to the same RVA).  The real implementation
// lives in CLO's host binary and is reachable only through the live vtable of the
// UTILITY_API object — hooking the DLL export is a no-op.
//
// Vtable slot counted from UtilityAPIInterface.h in declaration order.
// MSVC x64 prepends 2 destructor slots before the first virtual method ONLY when
// a virtual destructor exists. UtilityAPIInterface has none, so slot 0 is the
// first declared virtual method:
//   slot 0  GetCLOTemporaryFolderPath  slot 1  GetCLOTemporaryFolderPathW
//   slot 2  DisplayMessageBox          slot 3  DisplayMessageBoxW
//   slot 4  GetProjectName             slot 5  GetProjectNameW
//   slot 6  GetProjectFilePath         slot 7  GetProjectFilePathW
//   slot 8  GetMajorVersion            slot 9  GetMinorVersion
//   slot 10 GetPatchVersion            slot 11 toUtf8
//   slot 12 GetColorwayCount           slot 13 GetCurrentColorwayIndex
//   slot 14 SetCurrentColorwayIndex    slot 15 SetColorwayName
//   slot 16 SetColorwayNameW           slot 17 GetColorwayName
//   slot 18 GetColorwayNameW           slot 19 CopyColorway
//   slot 20 GetCustomViewInformation   slot 21 GetCustomViewInformationW
//   slot 22 GetClothPositions          slot 23 ResetClothArrangement
//   slot 24 GetThumbnailInCLOFile
//   slot 25 SaveCLOFileThumbnail(string,string,uint)
//   slot 26 SaveCLOFileThumbnail(string,wstring,uint)
//   slot 27 GetAssetIconInCLOFile
//   slot 28 GetMetaDataForCurrentGarment
//   slot 29 GetMetaDataForCurrentGarmentW
//   slot 30 SetMetaDataForCurrentGarment
//   slot 31 ChangeMetaDataValueForCurrentGarment
//   slot 32 CreateProgressBar   ← target
//
// NOTE: UtilityAPIInterface has NO virtual destructor (??1UtilityAPIInterface is
// absent from CLOAPIInterface.dll exports, while constructors ARE exported — MSVC
// exports all non-inline members when __declspec(dllexport) is on the class, so
// the absence is conclusive). No destructor slots → first virtual method is slot 0.
// ImportAPIInterface DOES have a virtual destructor (??1ImportAPIInterface exported)
// so its vtable is offset by +2, but UtilityAPIInterface is not.
constexpr int kCreateProgressBarVtableSlot = 32;

using CreateProgressBarFn = void(*)(void*);
static uint64_t        s_createProgressBarOriginal = 0;
static PLH::x64Detour* s_createProgressBarDetour   = nullptr;

static void hookCreateProgressBar(void* self)
{
    LOG_INFO("CreateProgressBar hook!!!");
    reinterpret_cast<CreateProgressBarFn>(s_createProgressBarOriginal)(self);
}

// ── std::basic_ios<wchar_t>::rdbuf() const — msvcp140 raw hook ───────────────
// rdbuf() is defined INLINE in MSVC's <ios> header.  Taking
// &std::basic_ios<wchar_t>::rdbuf in C++ code yields the address of a local
// COMDAT copy inside Extensions.dll — NOT the copy CLO actually calls, which
// lives in msvcp140.dll.  HooksManager::addAfter<...> therefore hooks the wrong
// address and the callback never fires.
//
// Fix: resolve the real address from msvcp140.dll via GetProcAddress, then
// install a raw PLH::x64Detour on it — exactly the same pattern used above for
// CreateProgressBar and ImportAvatar.
//
// Mangled name confirmed from msvcp140.dll export table (#A8B0 in the comments
// in ExtensionsManager):
//   ?rdbuf@?$basic_ios@_WU?$char_traits@_W@std@@@std@@QEBAPEAV?$basic_streambuf@_WU?$char_traits@_W@std@@@2@XZ
//
// Signature: std::basic_streambuf<wchar_t>* __cdecl (const std::basic_ios<wchar_t>*)
// MSVC x64 ABI passes implicit 'this' as first argument (RCX).
using RdbufWFn = std::basic_streambuf<wchar_t>*(*)(const std::basic_ios<wchar_t>*);
static uint64_t        s_rdbufWOriginal = 0;
static PLH::x64Detour* s_rdbufWDetour   = nullptr;

static std::basic_streambuf<wchar_t>* hookRdbufW(const std::basic_ios<wchar_t>* self)
{
    auto* result = reinterpret_cast<RdbufWFn>(s_rdbufWOriginal)(self);
    qDebug() << "RD BUFFER" << result;
    return result;
}

// ── ImportAPIInterface::ImportAvatar vtable hook ──────────────────────────────
// Same stub problem as CreateProgressBar: ImportAvatar (RVA 0x00002500) has a
// unique address in the SDK DLL, but live calls still go through the vtable of
// the real IMPORT_API object in CLO's host binary — HooksManager's vcall thunk
// detour is bypassed by direct vtable dispatch.
//
// ImportAPIInterface HAS a virtual destructor (??1ImportAPIInterface exported)
// → 2 destructor slots prefix the vtable → first declared method is slot 2.
//
//   slot 0  ~ImportAPIInterface (scalar dtor)
//   slot 1  ~ImportAPIInterface (vector dtor)
//   slot 2  ImportFile(string)              slot 3  ImportFileW
//   slot 4  ImportZprj                      slot 5  ImportZprjW
//   slot 6  ImportGarmentInformation        slot 7  ImportGarmentInformationW
//   slot 8  ImportGarmentInformationConfigData  slot 9  ...ConfigDataW
//   slot 10 ImportOBJ                       slot 11 ImportOBJW
//   slot 12 ImportVMP                       slot 13 ImportVMPW
//   slot 14 ImportCPT                       slot 15 ImportCPTW
//   slot 16 ImportVLP                       slot 17 ImportVLPW
//   slot 18 ImportVRP                       slot 19 ImportVRPW
//   slot 20 ImportDXF                       slot 21 ImportDXFW
//   slot 22 ImportGraphicStyleFromImage(string)  slot 23 ...(wstring)
//   slot 24 ImportAVAC(wstring,wstring)     slot 25 ImportAVAC(string,string)
//   slot 26 ImportFile(string,ImportExportOption)  slot 27 ImportFileW(...)
//   slot 28 ImportFBX                       slot 29 ImportFBXW
//   slot 30 ImportGLTF                      slot 31 ImportGLTFW
//   slot 32 ImportSMP                       slot 33 ImportSMPW
//   slot 34 ImportAsGraphic                 slot 35 ImportAsGraphicW
//   slot 36 ImportTrim
//   slot 37 ImportAvatar   ← target  (confirmed from real DLL vtable binary)
//   NOTE: header-based count gives slot 38, but the real CLO binary has one
//   additional hidden internal method inserted before ImportAvatar, shifting it down by 1.
constexpr int kImportAvatarVtableSlot = 37;

// Signature matches the header: bool ImportAvatar(std::string _avtPath, ImportExportOption _opt)
// Both args are passed BY VALUE — must match exactly or the stack frame is wrong.
using ImportAvatarFn = bool(*)(void*, std::string, Marvelous::ImportExportOption);
static uint64_t        s_importAvatarOriginal = 0;
static PLH::x64Detour* s_importAvatarDetour   = nullptr;

static bool hookImportAvatar(void* self, std::string _avtPath, Marvelous::ImportExportOption _opt)
{
    LOG_INFO("!!!Importing Avatar {}", _avtPath);
    return reinterpret_cast<ImportAvatarFn>(s_importAvatarOriginal)(self, std::move(_avtPath), _opt);
}

void ExtensionsManager::registerExtension(Extension *extension) {
    extensions.push_back(extension);
}

#include <QMap>
#include <QQueue>

QMap<Qt::HANDLE, QQueue<QPointer<QObject>>> constructionQueue {};

static void firstAddHook(QObject *object)
{
    if (constructionQueue.contains(QThread::currentThreadId())) {
        QQueue<QPointer<QObject>>& currentQueue = constructionQueue[QThread::currentThreadId()];
        while (!currentQueue.empty()) {
            QPointer<QObject> p = currentQueue.dequeue();
            if (p) {
                if (QString("AuthenticationProcessor") == p.data()->metaObject()->className()) {
                    auto authenticationProcessor = p.data();
                    HooksManager::addBefore<&QApplication::exec>([authenticationProcessor](const HookHandle& handle) {
                        for (const auto widget: QApplication::allWidgets()) {
                            if (QString("CloUICommon::LoginDialog") == widget->metaObject()->className()) {
                                LOG_INFO("CloUICommon::LoginDialog");
                                QMetaObject::invokeMethod(authenticationProcessor, "SucceedAuthentication");
                                QMetaObject::invokeMethod(widget, "SignInWithCloset");
                                LOG_INFO("EXIT");
                                handle.remove();
                            }
                        }
                    });
                }
                // LOG_INFO("Thread: {}. Class: {}. TypeID: {}. Object: {}", QThread::currentThreadId(), p.data()->metaObject()->className(), typeid(*(p.data())).name(), p.data()->objectName().toStdString());
            }
        }
    } else {
        constructionQueue[QThread::currentThreadId()] = {};
    }
    constructionQueue[QThread::currentThreadId()].enqueue(object);
}

#include <QTextStream>

class filebuf : public std::basic_streambuf<char> {
public:
    std::streamsize xsputn(const char*, std::streamsize);
};

void ExtensionsManager::install() {
    qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(&firstAddHook);

    // ── std::basic_ios<wchar_t>::rdbuf — raw hook (see header comment above) ──
    {
        constexpr const char* kSym =
            "?rdbuf@?$basic_ios@_WU?$char_traits@_W@std@@@std@@"
            "QEBAPEAV?$basic_streambuf@_WU?$char_traits@_W@std@@@2@XZ";
        const HMODULE hMsvcp = GetModuleHandleA("msvcp140.dll");
        if (hMsvcp) {
            const auto addr = reinterpret_cast<uint64_t>(GetProcAddress(hMsvcp, kSym));
            if (addr) {
                s_rdbufWDetour = new PLH::x64Detour(addr,
                    reinterpret_cast<uint64_t>(&hookRdbufW),
                    &s_rdbufWOriginal);
                s_rdbufWDetour->hook();
                LOG_INFO("rdbuf<wchar_t> hook installed at {:x}", addr);
            } else {
                LOG_WARN("rdbuf<wchar_t>: symbol not found in msvcp140.dll — hook skipped");
            }
        } else {
            LOG_WARN("msvcp140.dll not loaded — rdbuf hook skipped");
        }
    }

    HooksManager::addAfter<&QWidget::show>([](const HookHandle& handle, QWidget* this_) {
        if (this_->objectName() == " TitleFrame") {
            LOG_INFO("Main window has been detected by Extensions Manager. Setting up UI.");
            mainWindow = dynamic_cast<QFrame*>(this_);
            for (const auto widget: QApplication::allWidgets()) {
                for (const auto extension: extensions) {
                    extension->configure(widget);
                }
            }
        } else if (this_->objectName() == "myMenuBar") {
            LOG_INFO("Configuring \"Extensions\" menu.");
            const auto menuBar = qobject_cast<QMenuBar *>(this_);
            const auto extensionsMenu = menuBar->addMenu("Extensions");

            extensionsSettings = new ExtensionsSettings(mainWindow);
            const QAction *extensionsSettingsMenu = extensionsMenu->addAction("Extensions Settings");
            QObject::connect(extensionsSettingsMenu, &QAction::triggered, extensionsSettings, &ExtensionsSettings::exec);

            for (const auto extension: extensions) {
                extension->configureMenu(extensionsMenu);
            }
        } else if (QString(this_->metaObject()->className()) == "MVStatusBar") {
            LOG_INFO("Configuring status bar.");
            for (const auto statusBar = dynamic_cast<MVStatusBar*>(this_);
                 const auto child: statusBar->children()) {
                if (child->metaObject() == &QWidget::staticMetaObject && !child->children().empty()) {
                    const auto parent = qobject_cast<QWidget *>(child);
                    backgroundMessage_ = new QLabel(parent);
                    backgroundMessage_->setGeometry(statusBar->width() / 2, 2, 500, 20);
                    UTILITY_API->UpdateCloStyleForPlugIn(backgroundMessage_);
                    backgroundMessage_->show();

                    for (const auto extension: extensions) {
                        extension->configureStatusBar(parent);
                    }
                }
            }
            LOG_INFO("EXIT2");
            // handle.remove();
        }
        // LOG_INFO("Class: {}. Object: {}", this_->metaObject()->className(), this_->objectName().toStdString());
    });

    HooksManager::addIgnore<&qInstallMessageHandler>([](const HookHandle&, bool& ignore, QtMessageHandler&, QtMessageHandler&) {
        ignore = true;
    });

    HooksManager::addIgnore<&QDesktopServices::openUrl>(
        [](const HookHandle &handle, bool& ignore, bool& ret, const QUrl &url) {
            if (url.toString().startsWith("https://style.clo-set.com/en/account/signin?productId=40")) {
                LOG_DEBUG("Bypassing login URL: {}", url.toString().toStdString());
                ignore = true;
                ret = true;
                handle.remove();
            }
        });

    HooksManager::addAfter<&QObject::setObjectName>([](const HookHandle&, QObject* this_, const QString& name) {
        if (name.contains("MeasureID")) {
            LOG_INFO("Measure: {}. Class: {}", name.toStdString(), this_->metaObject()->className());
            if (const auto spinBox = qobject_cast<QDoubleSpinBox*>(this_)) {
                spinBox->connect(spinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), [](double value) {
                    LOG_INFO("new value: {}", value);
                });
            }
        }
    });

    // HooksManager::addBefore<&QFileDevicePrivate::read>([](const HookHandle&, QIODevicePrivate* this_, char *data, qint64 maxSize, bool peeking) {
    //     std::cout << data << std::endl;
    // });

    HooksManager::addBefore<qOverload<const char*, qint64>(&QIODevice::write)>([](const HookHandle&, QIODevice* this_, const char *data, qint64 len) {
        std::cout << data << std::endl;
    });

    //msvcp140.public: class std::basic_ostream<unsigned short, struct std::char_traits<unsigned short>> & __cdecl std::basic_ostream<unsigned short, struct std::char_traits<unsigned short>>::operator<<(class std::basic_ostream<unsigned short, struct std::char_traits<un
    //.text:00007FFB19333180 msvcp140.dll:$43180 #42580 <public: class std::basic_ostream<char, struct std::char_traits<char>> & __cdecl std::basic_ostream<char, struct std::char_traits<char>>::operator<<(float)>

    //Address=00007FF67A3C8170
    // Type=Import
    // Symbol=msvcp140.?sputn@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAA_JPEBD_J@Z
    // Symbol (undecorated)=public: __int64 __cdecl std::basic_streambuf<char, struct std::char_traits<char>>::sputn(char const *, __int64)

    //msvcp140.??6?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAAAEAV01@P6AAEAV01@AEAV01@@Z@Z

    // HooksManager::addBefore<qOverload<const char*>(&QTextStream::operator<<)>([](
    //     const HookHandle&, QTextStream* this_, const char* text) {
    //     qDebug() << text;
    // });
    //
    // HooksManager::addBefore<qOverload<const QString &>(&QTextStream::operator<<)>([](
    //     const HookHandle&, QTextStream* this_, const QString &s) {
    //     qDebug() << s;
    // });

    // HooksManager::addBefore<qOverload<signed int>(&QTextStream::operator<<)>([](
    //     const HookHandle&, QTextStream* this_, signed int i) {
    //     qDebug() << text;
    // });

    // HooksManager::addBefore<&fwrite>([](const HookHandle&, void const* _Buffer, size_t _ElementSize, size_t _ElementCount, FILE *) {
    //     size_t total = _ElementSize * _ElementCount;
    //
    //     if (!_Buffer || total == 0)
    //         return;
    //
    //     const char *data = static_cast<const char *>(_Buffer);
    //
    //     QByteArray arr(data, static_cast<int>(total));
    //
    //     // Try as text
    //     qDebug() << "fwrite text:" << arr;
    //
    //     // Always safe: hex dump
    //     qDebug() << "fwrite hex:" << arr.toHex();
    // });

    // using Fn = std::basic_ostream<char>& (std::basic_ostream<char>::*)(char);
    // Fn fn = [](std::basic_ostream<char>& os, char c) -> std::basic_ostream<char>& {
    //     return os.operator<<(c);
    //

    //.text:00007FFB1D6BB4B0 msvcp140.dll:$B4B0 #A8B0 <public: class std::basic_streambuf<wchar_t, struct std::char_traits<wchar_t>> * __cdecl std::basic_ios<wchar_t, struct std::char_traits<wchar_t>>::rdbuf(void) const>

    // .text:00007FFB1D6BB4B0 msvcp140.dll:$B4B0 #A8B0 <public: class std::basic_streambuf<wchar_t, struct std::char_traits<wchar_t>> * __cdecl std::basic_ios<wchar_t, struct std::char_traits<wchar_t>>::rdbuf(void) const>
    // HooksManager::addBefore<static_cast<std::basic_ostream<char, struct std::char_traits<char>>& (std::basic_ostream<char, struct std::char_traits<char>>::*)(float)>(&std::basic_ostream<char, struct std::char_traits<char>>::operator<<)>(
    //     [](const HookHandle &, std::basic_ostream<char, struct std::char_traits<char>>*, float _Val) {
    //     // qDebug() << _Val;
    // });

    // HooksManager::addBefore<&std::basic_ostream<char>::put>(
    //     [](const HookHandle &, std::basic_ostream<char>* this_, char c) {
    //         qDebug() << "Char" << static_cast<int>(c);
    // });

   //  HooksManager::addBefore<&std::basic_streambuf<unsigned short>::getloc>(
   //     [](const HookHandle &, const std::basic_streambuf<unsigned short>*) {
   //         qDebug() << "Get LOCALE";
   // });

    // public: __cdecl std::basic_ostream<char, struct std::char_traits<char>>::basic_ostream<char, struct std::char_traits<char>>(class std::basic_streambuf<char, struct std::char_traits<char>> *, bool)
    // public: class std::locale __cdecl std::basic_streambuf<unsigned short, struct std::char_traits<unsigned short>>::getloc(void) const
    // public: __int64 __cdecl std::basic_streambuf<char, struct std::char_traits<char>>::sputn(char const *, __int64)
    // HooksManager::addBefore<&std::basic_streambuf<char>::sputn>(
    //     [](const HookHandle &, std::basic_streambuf<char>*, char const * text, std::streamsize size) {
    //         // if (text) qDebug() << "TEXT" << ret;
    // });

    //public: char __cdecl std::basic_ios<char, struct std::char_traits<char>>::widen(char) const

    // HooksManager::addBefore<&std::basic_ostream<char, struct std::char_traits<char>>::init>(
    //     [](const HookHandle &, std::basic_streambuf<char>*, char const * text, std::streamsize size) {
    //         // qDebug() << "TEXT" << text;
    // });

    // public: class std::basic_ostream<unsigned short, struct std::char_traits<unsigned short>> & __cdecl std::basic_ostream<unsigned short, struct std::char_traits<unsigned short>>::operator<<(class std::basic_ostream<unsigned short, struct std::char_traits<un

    // HooksManager::addBefore<&std::basic_ostream<wchar_t>::flush>(
    //     [](const HookHandle &, std::basic_ostream<wchar_t>* this_) {
    //         const auto buf = this_->rdbuf();
    //         if (buf) {
    //             std::wstring data;
    //             for (auto ch = buf->sgetc(); ch != WEOF; ch = buf->snextc()) {
    //                 data += static_cast<wchar_t>(ch);
    //             }
    //             std::wcout << data;
    //         }
    // });

    //public: class std::basic_ostream<wchar_t, struct std::char_traits<wchar_t>> & __cdecl std::basic_ostream<wchar_t, struct std::char_traits<wchar_t>>::flush(void)
    //public: class std::basic_ostream<char, struct std::char_traits<char>> & __cdecl std::basic_ostream<char, struct std::char_traits<char>>::put(char)
    // public: class std::basic_ostream<char, struct std::char_traits<char>> & __cdecl std::basic_ostream<char, struct std::char_traits<char>>::operator<<(class std::basic_ostream<char, struct std::char_traits<char>> & (__cdecl *)(class std::basic_ostream<char,
    // public: class std::basic_streambuf<wchar_t, struct std::char_traits<wchar_t>> * __cdecl std::basic_ios<wchar_t, struct std::char_traits<wchar_t>>::rdbuf(void) const
    // (rdbuf<wchar_t> hook installed above via raw PLH::x64Detour — see s_rdbufWDetour)

    // HooksManager::addBefore<&vfprintf>([](const HookHandle &,
    //     FILE*       const _Stream,
    //     char const* const _Format,
    //     va_list           _ArgList) {
    //     qDebug() << "vprintf:" << _Format;
    // });

    // HooksManager::addBefore<&vfprintf>([](const HookHandle&, FILE* const _Stream, char const* const _Format, ...) {
    //     qDebug() << "fprintf format:" << _Format;
    // });
    // HooksManager::addBefore<&QSettings::beginGroup>(
    //     [](const HookHandle& handle, QSettings* settings, const QString &prefix) {
    //         LOG_DEBUG(" --- Begin group {}. Settings: {}", prefix.toStdString(), reinterpret_cast<uintptr_t>(settings));
    //     });
    // HooksManager::addBefore<&QSettings::endGroup>(
    //     [](const HookHandle& handle, QSettings* settings) {
    //         LOG_DEBUG("End group Settings: {}", reinterpret_cast<uintptr_t>(settings));
    //     });
    //
    // HooksManager::addAfter<&QSettings::value>(
    // [](const HookHandle& handle, const QSettings* settings, QVariant* ret, const QString& key, const QVariant& defaultValue) {
    //     LOG_DEBUG("QSettings::value: key={} value={} default={}. Settings: {}",
    //               key.toStdString(), ret->toString().toStdString(),
    //               defaultValue.toString().toStdString(),
    //               reinterpret_cast<uintptr_t>(settings));
    //     LOG_DEBUG("Group: {}", settings->group().toStdString());
    //     std::cout << "Settings" << settings << std::endl;
    // });
    //
    // HooksManager::addAfter<&QSettings::setValue>(
    // [](const HookHandle& handle, QSettings*& settings, const QString &key, const QVariant &value) {
    //     LOG_DEBUG("QSettings::setValue: key={} value={} Settings: {}", key.toStdString(), value.toString().toStdString(), reinterpret_cast<uintptr_t>(settings));
    // });

    // HooksManager::addBefore<&QObjectPrivate::addConnection>([&](const HookHandle& handle, const QObjectPrivate* obj, const int signal, const QObjectPrivate::Connection *c) {
    //     if (c->sender &&
    //         (!QString(c->sender->metaObject()->className()).startsWith("Q")
    //         || QString(c->sender->metaObject()->className()) == "QAction"
    //         || QString(c->sender->metaObject()->className()) == "QMenu")
    //         ) {
    //         const QMetaObject *mo = c->sender->metaObject();
    //         // Resolve signal name: signalIdx is 0-based counting only Signal methods
    //         // across the full metaobject hierarchy (including inherited).
    //         int sigCount = 0;
    //         for (int i = 0; i < mo->methodCount(); ++i) {
    //             if (mo->method(i).methodType() == QMetaMethod::Signal) {
    //                 if (sigCount == signal) {
    //                     LOG_DEBUG("addConnection  {}({})::{}  →  {}({})",
    //                               mo->className(),
    //                               c->sender->objectName().toStdString(),
    //                               mo->method(i).methodSignature().constData(),
    //                               c->receiver ? c->receiver.loadAcquire()->metaObject()->className() : "<null>",
    //                               c->receiver ? c->receiver.loadAcquire()->objectName().toStdString() : "");
    //
    //                     for (const QMetaObject *m = mo; m != nullptr; m = m->superClass()) {
    //                         if (QString(m->className()).startsWith("Q")) continue;
    //                         LOG_DEBUG("=== {} === Parent: {}", m->className(), obj->parent ? obj->parent->metaObject()->className() : "NULL");
    //
    //                         for (int j = m->methodOffset(); j < m->methodOffset() + m->methodCount(); ++j) {
    //                             const QMetaMethod method = m->method(j);
    //
    //                             const char *typeLabel = nullptr;
    //                             switch (method.methodType()) {
    //                                 case QMetaMethod::Signal: typeLabel = "SIGNAL";
    //                                     break;
    //                                 case QMetaMethod::Slot: typeLabel = "SLOT  ";
    //                                     break;
    //                                 default: continue; // skip QMetaMethod::Method and Constructor
    //                             }
    //
    //                             LOG_DEBUG("  [{}] {}", typeLabel, method.methodSignature().constData());
    //                         }
    //                     }
    //
    //                     if (QString("CloUICommon::CVFSignOnWorker") == mo->className()) {
    //                         LOG_INFO("FOUND CloUICommon::CVFSignOnWorker");
    //                         test = c->sender;
    //                     } else if (QString("AuthenticationProcessor") == mo->className()) {
    //                         LOG_INFO("FOUND AuthenticationProcessor");
    //                         ap = c->sender;
    //                     }
    //
    //                     QString h = mo->className();
    //                     do {
    //                         mo = mo->superClass();
    //                         h.append(" ").append(mo->className());
    //                     } while (mo->superClass());
    //                     LOG_DEBUG(" --- {}", h.toStdString());
    //
    //                     break;
    //                 }
    //                 ++sigCount;
    //             }
    //         }
    //     }
    // });
    //
    // HooksManager::addBefore<static_cast<void(*)(QObject*, const QMetaObject*, int, void**)>(&QMetaObject::activate)>([&](const HookHandle& handle, QObject *sender, const QMetaObject *m, int local_signal_index, void **argv) {
    //     if (sender && m &&
    //         (!QString(sender->metaObject()->className()).startsWith("Q")
    //         || QString(sender->metaObject()->className()) == "QAction"
    //         || QString(sender->metaObject()->className()) == "QMenu")
    //         || QString(
    //             sender->metaObject()->className()).contains("Network")
    //             ) {
    //         const int absIdx = m->methodOffset() + local_signal_index;
    //         const QMetaMethod sig = sender->metaObject()->method(absIdx);
    //         const auto sigName = sig.methodSignature();
    //
    //         const QByteArray macroSig = QByteArray("2") + sigName;
    //         const auto modifiedSender = static_cast<Hack *>(sender);
    //         const auto numOfReceivers = modifiedSender->receivers(macroSig.constData());
    //
    //         if (numOfReceivers > 0) {
    //             LOG_DEBUG("emit  {}({})::{} receivers: {}",
    //                       sender->metaObject()->className(),
    //                       sender->objectName().toStdString(),
    //                       sigName.constData(), numOfReceivers);
    //         }
    //     }
    // });
}

void ExtensionsManager::setMessage(const QString &message) {
    QMetaObject::invokeMethod(backgroundMessage_, [message] {
        backgroundMessage_->setText(message);
        backgroundMessage_->repaint();
    });
}

void ExtensionsManager::setMessage(const QString &extensionName, const QString &message,
                                   const bool logMessage) {
    if (logMessage) LOG_INFO_TO(extensionName.toStdString(), "{}", message.toStdString());
    setMessage(QString("<img src=':/Resources/CommonIcon/Title Bullet Secondary.svg' width='11' height='11'><b>%1:</b> %2").arg(extensionName).arg(message));
}

void ExtensionsManager::clearMessage() {
    setMessage("");
}