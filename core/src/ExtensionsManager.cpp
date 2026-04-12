#include "ExtensionsManager.h"

#define LOGGER_NAME "Extensions Manager"

#include <windows.h>
#include <QApplication>
#include <QMenuBar>
#include <QMetaMethod>

#include <QDesktopServices>
#include <QUrl>
#include <QtCore/private/qobject_p.h>
#include <QtCore/private/qhooks_p.h>
#include <QtCore/qobjectdefs.h>
#include <QDebug>
#include <qthreadpool.h>

#include "ExtensionsSettings.h"

#include "HooksManager.h"
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

static void firstAddHook(QObject *obj)
{
    QThreadPool::globalInstance()->start([=]() {
        LOG_INFO("Class: {}. TypeID: {}. Object: {}", "obj->metaObject()->className()", typeid(*obj).name(), "obj->objectName().toStdString()");
    });
}

static void startupHook()
{
    LOG_INFO("Startup Hook");
    // std::cout << "HOOK!!!";
    // LOG_INFO("HOOK!!!");
    qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(&firstAddHook);
}

void ExtensionsManager::install() {

    // qtHookData[QHooks::Startup] = reinterpret_cast<quintptr>(&startupHook);

    // ── CLO API vtable hooks ───────────────────────────────────────────────
    // UTILITY_API and IMPORT_API are guaranteed live here — CLO initialises
    // all API objects before entering QApplication::exec.
    // if (UTILITY_API) {
    //     void** vtable = *reinterpret_cast<void***>(UTILITY_API);
    //     void*  realFn =  vtable[kCreateProgressBarVtableSlot];
    //     LOG_INFO("CreateProgressBar real address (vtable[{}]): {:p}", kCreateProgressBarVtableSlot, realFn);
    //     s_createProgressBarDetour = new PLH::x64Detour(
    //         reinterpret_cast<uint64_t>(realFn),
    //         reinterpret_cast<uint64_t>(&hookCreateProgressBar),
    //         &s_createProgressBarOriginal);
    //     s_createProgressBarDetour->hook()
    //         ? LOG_INFO("CreateProgressBar vtable hook installed")
    //         : LOG_CRITICAL("CreateProgressBar vtable hook FAILED");
    // } else {
    //     LOG_CRITICAL("UTILITY_API is null — CreateProgressBar hook skipped");
    // }
    //
    // if (IMPORT_API) {
    //     void** vtable = *reinterpret_cast<void***>(IMPORT_API);
    //     void*  realFn =  vtable[kImportAvatarVtableSlot];
    //     LOG_INFO("ImportAvatar real address (vtable[{}]): {:p}", kImportAvatarVtableSlot, realFn);
    //     s_importAvatarDetour = new PLH::x64Detour(
    //         reinterpret_cast<uint64_t>(realFn),
    //         reinterpret_cast<uint64_t>(&hookImportAvatar),
    //         &s_importAvatarOriginal);
    //     s_importAvatarDetour->hook()
    //         ? LOG_INFO("ImportAvatar vtable hook installed")
    //         : LOG_CRITICAL("ImportAvatar vtable hook FAILED");
    // } else {
    //     LOG_CRITICAL("IMPORT_API is null — ImportAvatar hook skipped");
    // }

    HooksManager::addBefore<&QApplication::exec>([&](const HookHandle &handle) {

        LOG_INFO("QApplication::exec()");

        for (const auto& widget: QApplication::allWidgets()) {
            if (QString(widget->metaObject()->className()) == "CloUICommon::LoginDialog") {
                QMetaObject::invokeMethod(ap, "SucceedAuthentication");
                QMetaObject::invokeMethod(widget, "SignInWithCloset");
                // QMetaObject::invokeMethod(test, "LoginSucceed", Q_ARG(QString, "hello"));
            }
        }

        // QMenuBar* menu = nullptr;
        //
        // for (const auto widget: QApplication::allWidgets()) {
        //     // Configure main window
        //     if (widget->objectName() == "TitleFrame") {
        //         mainWindow = dynamic_cast<QFrame*>(widget);
        //         LOG_INFO("Main window has been detected by Extensions Manager.");
        //     }
        //
        //     // Getting menu bar for further configuration
        //     else if (widget->objectName() == "myMenuBar") menu = qobject_cast<QMenuBar*>(widget);
        //
        //     // Inject QLabel for displaying messages from background processes into bottom status bar.
        //     else if (QString(widget->metaObject()->className()) == "MVStatusBar") {
        //         for (const auto statusBar = dynamic_cast<MVStatusBar*>(widget);
        //              const auto child: statusBar->children()) {
        //             if (child->metaObject() == &QWidget::staticMetaObject && !child->children().empty()) {
        //                 const auto parent = qobject_cast<QWidget*>(child);
        //                 backgroundMessage_ = new QLabel(parent);
        //                 backgroundMessage_->setGeometry(statusBar->width() / 2, 2, 500, 20);
        //                 UTILITY_API->UpdateCloStyleForPlugIn(backgroundMessage_);
        //                 backgroundMessage_->show();
        //
        //                 for (const auto extension: extensions) {
        //                     extension->configureStatusBar(parent);
        //                 }
        //             }
        //         }
        //     }
        //
        //     for (const auto extension: extensions) {
        //         extension->configure(widget);
        //     }
        // }
        //
        // if (!menu) {
        //     LOG_CRITICAL("Menu was not found");
        //     exit(1);
        // }
        //
        // // Configuring menu
        // const auto extensionsMenu = menu->addMenu("Extensions");
        //
        // extensionsSettings = new ExtensionsSettings(mainWindow);
        // const QAction *extensionsSettingsMenu = extensionsMenu->addAction("Extensions Settings");
        // QObject::connect(extensionsSettingsMenu, &QAction::triggered, extensionsSettings, &ExtensionsSettings::exec);
        //
        // for (const auto extension: extensions) {
        //     extension->configureMenu(extensionsMenu);
        // }
        //
        // LOG_INFO("Extensions menu has been added to myMenuBar");
        // handle.remove();
    });

    // HooksManager::addBefore<static_cast<QDebug &(QDebug::*)(const char *t)>(&QDebug::operator<<)>(
    //     [&](const HookHandle handle, QDebug*, const char* m) {
    //         // LOG_DEBUG("DEBUG: {}", m);
    //     });

    HooksManager::addBefore<&QDesktopServices::openUrl>(
        [](const HookHandle &handle, const QUrl &url) {
            LOG_DEBUG("Redirecting to {}", url.toString().toStdString());
        });

    HooksManager::addBefore<&QSettings::beginGroup>(
        [](const HookHandle& handle, QSettings*& settings, const QString &prefix) {
            LOG_DEBUG(" --- Begin group {}. Settings: {}", prefix.toStdString(), reinterpret_cast<uintptr_t>(settings));
        });
    HooksManager::addBefore<&QSettings::endGroup>(
        [](const HookHandle& handle, QSettings*& settings) {
            LOG_DEBUG("End group Settings: {}", reinterpret_cast<uintptr_t>(settings));
        });

    HooksManager::addAfter<&QSettings::value>(
    [](const HookHandle& handle, const QVariant& ret, const QSettings* settings, const QString& key, const QVariant& defaultValue) {
        // LOG_DEBUG("QSettings::value: key={} value={} default={}. Group: {}. Settings: {}", key.toStdString(), ret.toString().toStdString(), defaultValue.toString().toStdString(), settings->group().toStdString(), reinterpret_cast<uintptr_t>(settings));
            LOG_DEBUG("QSettings::value: key={} value={} default={}. Settings: {}", key.toStdString(), ret.toString().toStdString(), defaultValue.toString().toStdString(), reinterpret_cast<uintptr_t>(settings));
    });

    HooksManager::addAfter<&QSettings::setValue>(
    [](const HookHandle& handle, QSettings*& settings, const QString &key, const QVariant &value) {
        LOG_DEBUG("QSettings::setValue: key={} value={} Settings: {}", key.toStdString(), value.toString().toStdString(), reinterpret_cast<uintptr_t>(settings));
    });

    HooksManager::addAfter<&QObjectPrivate::checkForIncompatibleLibraryVersion>([](const HookHandle& handle, const QObjectPrivate* objectPrivate, int&) {
        // LOG_DEBUG("ObjectPrivate: {}", reinterpret_cast<uintptr_t>(objectPrivate));
    });

    HooksManager::addBefore<&QObjectPrivate::addConnection>([&](const HookHandle& handle, const QObjectPrivate* obj, const int signal, const QObjectPrivate::Connection *c) {
        if (c->sender && !QString(c->sender->metaObject()->className()).startsWith("Q")) {
            const QMetaObject *mo = c->sender->metaObject();
            // Resolve signal name: signalIdx is 0-based counting only Signal methods
            // across the full metaobject hierarchy (including inherited).
            int sigCount = 0;
            for (int i = 0; i < mo->methodCount(); ++i) {
                if (mo->method(i).methodType() == QMetaMethod::Signal) {
                    if (sigCount == signal) {
                        LOG_DEBUG("addConnection  {}({})::{}  →  {}({})",
                                  mo->className(),
                                  c->sender->objectName().toStdString(),
                                  mo->method(i).methodSignature().constData(),
                                  c->receiver ? c->receiver.loadAcquire()->metaObject()->className() : "<null>",
                                  c->receiver ? c->receiver.loadAcquire()->objectName().toStdString() : "");

                        for (const QMetaObject *m = mo; m != nullptr; m = m->superClass()) {
                            if (QString(m->className()).startsWith("Q")) continue;
                            LOG_DEBUG("=== {} === Parent: {}", m->className(), obj->parent ? obj->parent->metaObject()->className() : "NULL");

                            for (int j = m->methodOffset(); j < m->methodOffset() + m->methodCount(); ++j) {
                                const QMetaMethod method = m->method(j);

                                const char *typeLabel = nullptr;
                                switch (method.methodType()) {
                                    case QMetaMethod::Signal: typeLabel = "SIGNAL";
                                        break;
                                    case QMetaMethod::Slot: typeLabel = "SLOT  ";
                                        break;
                                    default: continue; // skip QMetaMethod::Method and Constructor
                                }

                                LOG_DEBUG("  [{}] {}", typeLabel, method.methodSignature().constData());
                            }
                        }

                        if (QString("CloUICommon::CVFSignOnWorker") == mo->className()) {
                            LOG_INFO("FOUND CloUICommon::CVFSignOnWorker");
                            test = c->sender;
                        } else if (QString("AuthenticationProcessor") == mo->className()) {
                            LOG_INFO("FOUND AuthenticationProcessor");
                            ap = c->sender;
                        }

                        QString h = mo->className();
                        do {
                            mo = mo->superClass();
                            h.append(" ").append(mo->className());
                        } while (mo->superClass());
                        LOG_DEBUG(" --- {}", h.toStdString());

                        break;
                    }
                    ++sigCount;
                }
            }
        }
    });

    HooksManager::addBefore<static_cast<void(*)(QObject*, const QMetaObject*, int, void**)>(&QMetaObject::activate)>([&](const HookHandle& handle, QObject *sender, const QMetaObject *m, int local_signal_index, void **argv) {
        if (sender && m && !QString(sender->metaObject()->className()).startsWith("Q") || QString(
                sender->metaObject()->className()).contains("Network")) {
            const int absIdx = m->methodOffset() + local_signal_index;
            const QMetaMethod sig = sender->metaObject()->method(absIdx);
            const auto sigName = sig.methodSignature();

            const QByteArray macroSig = QByteArray("2") + sigName;
            const auto modifiedSender = static_cast<Hack *>(sender);
            const auto numOfReceivers = modifiedSender->receivers(macroSig.constData());

            if (numOfReceivers > 0) {
                LOG_DEBUG("emit  {}({})::{} receivers: {}",
                          sender->metaObject()->className(),
                          sender->objectName().toStdString(),
                          sigName.constData(), numOfReceivers);
            }
        }
    });
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