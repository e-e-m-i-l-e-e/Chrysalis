#include "ExtensionsManager.h"

#define LOGGER_NAME "Extensions Manager"

#include <windows.h>
#include <QApplication>
#include <QMenuBar>
#include <QMetaMethod>

#include <QNetworkAccessManager>

#include "ExtensionsSettings.h"

#include "HooksManager.h"
#include "MVStatusBar.h"

// ── QObjectPrivate::connectImpl hook infrastructure ───────────────────────────
// QObjectPrivate::connectImpl is the internal dispatch point for ALL new-style
// connect() calls (pointer-to-member and functor overloads).
//
// Preferred over QObject::connectImpl because:
//   • Second parameter is int signal_index (absolute method index on sender's
//     metaobject) rather than void** — the signal name is directly readable via
//     sender->metaObject()->method(signal_index).name() with no pointer chasing.
//   • Public static (SA) vs private static (CA) — cleaner intent, same runtime
//     access pattern (both require GetProcAddress since qobject_p.h is private).
//
// Mangled symbol confirmed from .misc/Qt5Core demangled export table:
//   ?connectImpl@QObjectPrivate@@SA?AVConnection@QMetaObject@@PEBVQObject@@
//   H0PEAPEAXPEAVQSlotObjectBase@QtPrivate@@W4ConnectionType@Qt@@PEBHPEBU3@@Z
//
// QSlotObjectBase is forward-declared; we only pass the pointer through.
namespace QtPrivate { class QSlotObjectBase; }

using ConnectImplFn = QMetaObject::Connection(*)(
    const QObject*, int,
    const QObject*, void**,
    QtPrivate::QSlotObjectBase*, Qt::ConnectionType,
    const int*, const QMetaObject*);

static uint64_t        s_connectImplOriginal = 0;
static PLH::x64Detour* s_connectImplDetour   = nullptr;

// ── QObject::connect(char*, char*) hook infrastructure ────────────────────────
// Old-style SIGNAL/SLOT connections (connect(sender, SIGNAL(...), SLOT(...)))
// do NOT go through QObjectPrivate::connectImpl (A7A) or QMetaObject::connect
// (A73). Binary analysis of Qt5Core.dll confirmed:
//
//   connect(sender, SIGNAL(foo()), receiver, SLOT(bar()))
//     → QObject::connect(char*,char*)  A76  @ 0x1E49B0
//         → internal 0x1E3DA0
//             → internal 0x1E65F0
//                 (never reaches A73 or A7A)
//
// QObject::connect(const QObject*, char*, ...)  instance form (A74) also
// delegates to A76, so hooking A76 covers both call forms.
//
// The char* args carry the SIGNAL/SLOT macro prefix digit ("2foo()" / "1bar()").
// Strip index 0 to get the clean signature.
//
// Symbol confirmed from .misc/Qt5Core:
//   ?connect@QObject@@SA?AVConnection@QMetaObject@@PEBV1@PEBD01W4ConnectionType@Qt@@@Z
//   QObject::connect(const QObject*, const char*, const QObject*, const char*, Qt::ConnectionType)
using QObjectConnectCharFn = QMetaObject::Connection(*)(
    const QObject*, const char*,
    const QObject*, const char*,
    Qt::ConnectionType);

static uint64_t        s_qobjectConnectCharOriginal = 0;
static PLH::x64Detour* s_qobjectConnectCharDetour   = nullptr;

static QMetaObject::Connection hookQObjectConnectChar(
    const QObject* sender,   const char* signal,
    const QObject* receiver, const char* slot,
    Qt::ConnectionType type)
{
    if (sender && receiver && signal && slot) {
        if (!QString(sender->metaObject()->className()).startsWith("Q") ||
            !QString(receiver->metaObject()->className()).startsWith("Q")) {
            // Qt macros prepend "2" to signals and "1" to slots — skip it.
            // LOG_DEBUG("connect(SIGNAL/SLOT)  {}({})::{}  →  {}({})",
            //     sender->metaObject()->className(),
            //     sender->objectName().toStdString(),
            //     signal + 1,
            //     receiver->metaObject()->className(),
            //     receiver->objectName().toStdString());
        }
    }
    return reinterpret_cast<QObjectConnectCharFn>(s_qobjectConnectCharOriginal)(
        sender, signal, receiver, slot, type);
}

static QMetaObject::Connection hookConnectImpl(
    const QObject* sender,   int signalIndex,
    const QObject* receiver, void** slotPtr,
    QtPrivate::QSlotObjectBase* slot, Qt::ConnectionType type,
    const int* types, const QMetaObject* senderMeta)
{
    if (sender) {
        if (!QString(sender->metaObject()->className()).startsWith("Q") || receiver && !QString(receiver->metaObject()->className()).startsWith("Q")) {
            const QMetaMethod signal = sender->metaObject()->method(signalIndex);
            // LOG_DEBUG("connectImpl  {}({}) ::{}  →  {}({})",
            //     sender->metaObject()->className(),
            //     sender->objectName().toStdString(),
            //     signal.methodSignature().constData(),
            //     receiver ? receiver->metaObject()->className() : "<nullptr>",
            //     receiver ? receiver->objectName().toStdString() : "<nullptr>");
        }
    }
    return reinterpret_cast<ConnectImplFn>(s_connectImplOriginal)(
        sender, signalIndex, receiver, slotPtr, slot, type, types, senderMeta);
}

// ── QMetaObject::activate hook infrastructure ─────────────────────────────────
// activate() is called by MOC-generated code on every signal emission.
// Three overloads exist in Qt5Core.dll, all static, all exported.
//
// Overload 3 (primary — MOC path):
//   activate(QObject* sender, const QMetaObject* m, int local_signal_index, void** argv)
//   local_signal_index is relative to m. Absolute index = m->methodOffset() + local_signal_index.
//
// Overload 2 (legacy / Qt-internal):
//   activate(QObject* sender, int signal_index, void** argv)
//   signal_index is already the absolute method index on the sender's metaobject.
//
// Overload 1 (range form — rarely used):
//   activate(QObject* sender, int from_signal_index, int to_signal_index, void** argv)

// ── QObjectPrivate::addConnection hook ───────────────────────────────────────
// addConnection() is the single leaf called by EVERY connection path in Qt5:
//   - QObjectPrivate::connectImpl  (A7A) — new-style template connects
//   - QMetaObjectPrivate::connect  (unexported) — string/int old-style connects
// All other hooks (connectImpl, connect(char*), connect(QMetaMethod)) fire at
// the public entry points but miss any direct internal caller.  addConnection
// fires last, after the Connection struct is fully initialised, so sender,
// receiver and signal_index are all available.
//
// Connection struct layout (from qobject_p.h, x64):
//   offset  0 : ConnectionOrSignalVector::next  (8 bytes)
//   offset  8 : Connection **prev               (8 bytes)
//   offset 16 : QAtomicPointer<Connection> nextConnectionList (8 bytes)
//   offset 24 : Connection *prevConnectionList  (8 bytes)
//   offset 32 : QObject *sender                 (8 bytes)  ← c->sender
//   offset 40 : QAtomicPointer<QObject> receiver(8 bytes)  ← raw ptr to receiver
//
// QObjectData (base of QObjectPrivate):
//   offset  0 : vtable ptr   (8 bytes)
//   offset  8 : QObject *q_ptr                  ← sender confirmed via Q_ASSERT(c->sender == q_ptr)
//
// signal_index is the private 0-based signal index counting ALL signals in the
// metaobject hierarchy.  Enumerate methods to resolve the name.
//
// Symbol confirmed from .misc/Qt5Core (A73 call target in A7A at +0x22E):
//   ?addConnection@QObjectPrivate@@QEAAXHPEAUConnection@1@@Z
//   void QObjectPrivate::addConnection(int signal, QObjectPrivate::Connection*)
using AddConnectionFn = void(*)(void*, int, void*);

static uint64_t        s_addConnectionOriginal = 0;
static PLH::x64Detour* s_addConnectionDetour   = nullptr;

static QObject *test;

static void hookAddConnection(void* priv, int signalIdx, void* c)
{
    // sender is at q_ptr offset 8 inside QObjectData
    const auto sender = *reinterpret_cast<QObject**>(static_cast<char*>(priv) + 8);
    // receiver is at Connection offset 40 (QAtomicPointer stores raw ptr)
    const auto receiver = *reinterpret_cast<QObject**>(static_cast<char*>(c) + 40);

    if (sender && !QString(sender->metaObject()->className()).startsWith("Q")) {
        const QMetaObject* mo = sender->metaObject();
        // Resolve signal name: signalIdx is 0-based counting only Signal methods
        // across the full metaobject hierarchy (including inherited).
        int sigCount = 0;
        for (int i = 0; i < mo->methodCount(); ++i) {
            if (mo->method(i).methodType() == QMetaMethod::Signal) {
                if (sigCount == signalIdx) {
                    LOG_DEBUG("addConnection  {}({})::{}  →  {}({})",
                        mo->className(),
                        sender->objectName().toStdString(),
                        mo->method(i).methodSignature().constData(),
                        receiver ? receiver->metaObject()->className() : "<null>",
                        receiver ? receiver->objectName().toStdString() : "");

                    for (const QMetaObject* m = mo; m != nullptr; m = m->superClass())
                    {
                        if (QString(m->className()).startsWith("Q")) continue;
                        LOG_DEBUG("=== {} ===", m->className());

                        for (int j = m->methodOffset(); j < m->methodOffset() + m->methodCount(); ++j)
                        {
                            const QMetaMethod method = m->method(j);

                            const char* typeLabel = nullptr;
                            switch (method.methodType())
                            {
                                case QMetaMethod::Signal: typeLabel = "SIGNAL"; break;
                                case QMetaMethod::Slot:   typeLabel = "SLOT  "; break;
                                default: continue; // skip QMetaMethod::Method and Constructor
                            }

                            LOG_DEBUG("  [{}] {}", typeLabel, method.methodSignature().constData());
                        }
                    }

                    if (QString("CloUICommon::CVFSignOnWorker") == mo->className()) {
                        LOG_INFO("FOUND CloUICommon::CVFSignOnWorker");
                        test = sender;
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

    reinterpret_cast<AddConnectionFn>(s_addConnectionOriginal)(priv, signalIdx, c);
}

// ── QObjectPrivate::connectNotify hook ────────────────────────────────────────
// QMetaObjectPrivate::connect() — the unexported internal function every public
// connect() path ultimately converges to — calls sender->d->connectNotify(signal)
// after writing the connection.  QObjectPrivate::connectNotify (A7E @ 0x9B30) is
// the trampoline that reads q_ptr and dispatches to QObject::connectNotify()
// virtually.  Hooking A7E catches ALL connections regardless of which public
// connect() overload (or private direct call) established them.
//
// QObjectData layout (base of QObjectPrivate):
//   offset 0 : vtable ptr   (8 bytes)
//   offset 8 : QObject* q_ptr  ← sender
//
// Disassembly confirmed:
//   48 8b 49 08   mov rcx, [rcx+8]   ; load q_ptr
//   48 8b 01      mov rax, [rcx]     ; load sender vtable
//   48 ff 60 48   jmp [rax+0x48]     ; tail-call virtual connectNotify
//
// Symbol: ?connectNotify@QObjectPrivate@@QEAAXAEBVQMetaMethod@@@Z
//   void QObjectPrivate::connectNotify(const QMetaMethod& signal)
using ConnectNotifyFn = void(*)(void*, const QMetaMethod&);

static uint64_t        s_connectNotifyOriginal = 0;
static PLH::x64Detour* s_connectNotifyDetour   = nullptr;

static void hookConnectNotify(void* priv, const QMetaMethod& signal)
{
    // q_ptr is at offset 8 inside QObjectData (after vtable ptr)
    const auto sender = *reinterpret_cast<QObject**>(reinterpret_cast<char*>(priv) + 8);

    if (sender && !QString(sender->metaObject()->className()).startsWith("Q")) {
        // LOG_DEBUG("connectNotify  {}({})::{}",
        //     sender->metaObject()->className(),
        //     sender->objectName().toStdString(),
        //     signal.methodSignature().constData());
    }

    reinterpret_cast<ConnectNotifyFn>(s_connectNotifyOriginal)(priv, signal);
}

// ── QObject::connect(QMetaMethod) hook infrastructure ─────────────────────────
// QObject::connect(const QObject*, const QMetaMethod&, const QObject*,
//                  const QMetaMethod&, Qt::ConnectionType)  A75 @ 0x1E4370
//
// This overload is used when the caller already holds resolved QMetaMethod
// objects (e.g. CLO's own framework wiring connections programmatically after
// introspecting the meta-object tree). It goes through internal 0x1CC300 and
// never reaches QObjectPrivate::connectImpl (A7A) or QObject::connect(char*) (A76).
//
// QMetaMethod carries the full signature via methodSignature(), so no string
// stripping or index lookup is required.
//
// Symbol confirmed from .misc/Qt5Core:
//   ?connect@QObject@@SA?AVConnection@QMetaObject@@PEBV1@AEBVQMetaMethod@@01W4ConnectionType@Qt@@@Z
//   QObject::connect(const QObject*, const QMetaMethod&, const QObject*, const QMetaMethod&, ConnectionType)
using QObjectConnectMetaMethodFn = QMetaObject::Connection(*)(
    const QObject*, const QMetaMethod&,
    const QObject*, const QMetaMethod&,
    Qt::ConnectionType);

static uint64_t        s_qobjectConnectMetaMethodOriginal = 0;
static PLH::x64Detour* s_qobjectConnectMetaMethodDetour   = nullptr;

static QMetaObject::Connection hookQObjectConnectMetaMethod(
    const QObject* sender,   const QMetaMethod& signal,
    const QObject* receiver, const QMetaMethod& slot,
    Qt::ConnectionType type)
{
    if (sender && receiver) {
        if (!QString(sender->metaObject()->className()).startsWith("Q") ||
            !QString(receiver->metaObject()->className()).startsWith("Q")) {
            // LOG_DEBUG("connect(QMetaMethod)  {}({})::{}  →  {}({})",
            //     sender->metaObject()->className(),
            //     sender->objectName().toStdString(),
            //     signal.methodSignature().constData(),
            //     receiver->metaObject()->className(),
            //     receiver->objectName().toStdString());
        }
    }
    return reinterpret_cast<QObjectConnectMetaMethodFn>(s_qobjectConnectMetaMethodOriginal)(
        sender, signal, receiver, slot, type);
}

// ── QMetaObject::connectSlotsByName hook ──────────────────────────────────────
// connectSlotsByName() is called by MOC-generated setupUi() for every widget
// loaded from a .ui file.  It scans child objects by objectName and wires slots
// named on_<objectName>_<signal>() automatically — bypassing BOTH
// QObjectPrivate::connectImpl (A7A) AND QMetaObject::connect (A73).
// It calls internal, non-exported helpers directly, so neither of the two hooks
// above fires for these auto-connections.
//
// Strategy: call the original first so all connections are established, then
// walk the receiver's method table and report every slot whose name matches the
// on_<n>_<sig> convention (i.e. the ones that were just wired).
//
// Symbol confirmed from .misc/Qt5Core demangled export table:
//   ?connectSlotsByName@QMetaObject@@SAXPEAVQObject@@@Z
//   QMetaObject::connectSlotsByName(QObject*)
using ConnectSlotsByNameFn = void(*)(QObject*);

static uint64_t        s_connectSlotsByNameOriginal = 0;
static PLH::x64Detour* s_connectSlotsByNameDetour   = nullptr;

static void hookConnectSlotsByName(QObject* obj)
{
    reinterpret_cast<ConnectSlotsByNameFn>(s_connectSlotsByNameOriginal)(obj);

    if (obj && !QString(obj->metaObject()->className()).startsWith("Q")) {
        const QMetaObject* mo = obj->metaObject();
        for (int i = 0; i < mo->methodCount(); i++) {
            const QMetaMethod m = mo->method(i);
            if (m.methodType() != QMetaMethod::Slot) continue;
            const QByteArray sig = m.methodSignature();
            if (!sig.startsWith("on_")) continue;
            // LOG_DEBUG("connectSlotsByName  {}({}) auto-wired slot: {}",
            //     mo->className(),
            //     obj->objectName().toStdString(),
            //     sig.constData());
        }
    }
}

using ActivateMOCFn    = void(*)(QObject*, const QMetaObject*, int, void**);
using ActivateLegacyFn = void(*)(QObject*, int, void**);
using ActivateRangeFn  = void(*)(QObject*, int, int, void**);

static uint64_t        s_activateMOCOriginal    = 0;
static uint64_t        s_activateLegacyOriginal = 0;
static uint64_t        s_activateRangeOriginal  = 0;
static PLH::x64Detour* s_activateMOCDetour      = nullptr;
static PLH::x64Detour* s_activateLegacyDetour   = nullptr;
static PLH::x64Detour* s_activateRangeDetour    = nullptr;

struct Hack : QObject {
    using QObject::receivers;
};

struct TestObject: QObject {
    Q_OBJECT
public slots:
    void testSlot() {
        LOG_INFO("TEST SLOT: {}", "SignalForCloseSubToolbar()");
    }
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

// Primary MOC-generated path — resolves the signal name from m + local index.
static void hookActivateMOC(QObject* sender, const QMetaObject* m, int localIdx, void** argv)
{
    if (sender && m && !QString(sender->metaObject()->className()).startsWith("Q") || QString(sender->metaObject()->className()).contains("Network")) {
        const int absIdx = m->methodOffset() + localIdx;
        const QMetaMethod sig = sender->metaObject()->method(absIdx);
        const auto sigName = sig.methodSignature();

        const QByteArray macroSig = QByteArray("2") + sigName;
        const auto modifiedSender = static_cast<Hack*>(sender);
        const auto numOfReceivers = modifiedSender->receivers(macroSig.constData());

        if (numOfReceivers > 0) {
            LOG_DEBUG("emit  {}({})::{} receivers: {}",
            sender->metaObject()->className(),
            sender->objectName().toStdString(),
            sigName.constData(), numOfReceivers);
        }
    }
    reinterpret_cast<ActivateMOCFn>(s_activateMOCOriginal)(sender, m, localIdx, argv);
}

// Legacy absolute-index path — used by some Qt internals.
static void hookActivateLegacy(QObject* sender, int signalIdx, void** argv)
{
    if (sender) {
        const QMetaMethod sig = sender->metaObject()->method(signalIdx);
        LOG_DEBUG("emit(legacy)  {}({})::{}",
            sender->metaObject()->className(),
            sender->objectName().toStdString(),
            sig.methodSignature().constData());
    }
    reinterpret_cast<ActivateLegacyFn>(s_activateLegacyOriginal)(sender, signalIdx, argv);
}

// Range form — logs the first signal in the range (edge case, rarely fired).
static void hookActivateRange(QObject* sender, int fromIdx, int toIdx, void** argv)
{
    // if (sender) {
    //     const QMetaMethod sig = sender->metaObject()->method(fromIdx);
    //     LOG_DEBUG("emit(range {}-{})  {}({})::{}",
    //         fromIdx, toIdx,
    //         sender->metaObject()->className(),
    //         sender->objectName().toStdString(),
    //         sig.methodSignature().constData());
    // }
    reinterpret_cast<ActivateRangeFn>(s_activateRangeOriginal)(sender, fromIdx, toIdx, argv);
}

void ExtensionsManager::registerExtension(Extension *extension) {
    extensions.push_back(extension);
}

void ExtensionsManager::install() {
    // ── connectImpl hook: new-style template connect() overloads ─────────────
    // Covers: connect(sender, &Foo::signal, receiver, &Bar::slot, ...)
    //         connect(sender, &Foo::signal, functor, ...)
    // Does NOT cover old-style SIGNAL/SLOT macros — see QObject::connect(char*) hook below.

    // ── connectImpl hook: covers all new-style template connect() overloads ──
    // Symbol confirmed from Qt5Core.dll PE export table.
    constexpr const char* kConnectImplSymbol =
        "?connectImpl@QObjectPrivate@@SA?AVConnection@QMetaObject@@PEBVQObject@@"
        "H0PEAPEAXPEAVQSlotObjectBase@QtPrivate@@W4ConnectionType@Qt@@PEBHPEBU3@@Z";

    if (const HMODULE hQt5Core = GetModuleHandleA("Qt5Core.dll")) {
        if (const auto addr = GetProcAddress(hQt5Core, kConnectImplSymbol)) {
            s_connectImplDetour = new PLH::x64Detour(
                reinterpret_cast<uint64_t>(addr),
                reinterpret_cast<uint64_t>(&hookConnectImpl),
                &s_connectImplOriginal);
            s_connectImplDetour->hook();
            LOG_INFO("connectImpl hook installed (new-style signals covered)");
        } else {
            LOG_CRITICAL("connectImpl symbol not found in Qt5Core.dll");
        }
    } else {
        LOG_CRITICAL("Qt5Core.dll not loaded — connectImpl hook skipped");
    }

    // ── QObjectPrivate::addConnection hook: true catch-all ────────────────────
    // Called by both connectImpl (A7A) and QMetaObjectPrivate::connect after
    // every connection, regardless of which public entry point was used.
    constexpr const char* kAddConnectionSymbol =
        "?addConnection@QObjectPrivate@@QEAAXHPEAUConnection@1@@Z";

    if (const HMODULE hQt5Core = GetModuleHandleA("Qt5Core.dll")) {
        if (const auto addr = GetProcAddress(hQt5Core, kAddConnectionSymbol)) {
            s_addConnectionDetour = new PLH::x64Detour(
                reinterpret_cast<uint64_t>(addr),
                reinterpret_cast<uint64_t>(&hookAddConnection),
                &s_addConnectionOriginal);
            s_addConnectionDetour->hook();
            LOG_INFO("QObjectPrivate::addConnection hook installed (true catch-all)");
        } else {
            LOG_CRITICAL("QObjectPrivate::addConnection symbol not found in Qt5Core.dll");
        }
    }

    // ── QObjectPrivate::connectNotify hook: catch-all for every connection ────
    // Fires after QMetaObjectPrivate::connect() writes any connection, including
    // direct internal calls that bypass all public connect() overloads.
    constexpr const char* kConnectNotifySymbol =
        "?connectNotify@QObjectPrivate@@QEAAXAEBVQMetaMethod@@@Z";

    if (const HMODULE hQt5Core = GetModuleHandleA("Qt5Core.dll")) {
        if (const auto addr = GetProcAddress(hQt5Core, kConnectNotifySymbol)) {
            s_connectNotifyDetour = new PLH::x64Detour(
                reinterpret_cast<uint64_t>(addr),
                reinterpret_cast<uint64_t>(&hookConnectNotify),
                &s_connectNotifyOriginal);
            s_connectNotifyDetour->hook();
            LOG_INFO("QObjectPrivate::connectNotify hook installed (catch-all covered)");
        } else {
            LOG_CRITICAL("QObjectPrivate::connectNotify symbol not found in Qt5Core.dll");
        }
    }

    // ── QObject::connect(char*,char*) hook: old-style SIGNAL/SLOT connections ─
    // Binary analysis confirmed that SIGNAL/SLOT macros reach A76 directly and
    // never call QMetaObject::connect(int,int) (A73) in this Qt build.
    // A74 (instance form) delegates to A76, so one hook covers both forms.
    constexpr const char* kQObjectConnectCharSymbol =
        "?connect@QObject@@SA?AVConnection@QMetaObject@@PEBV1@PEBD01W4ConnectionType@Qt@@@Z";

    if (const HMODULE hQt5Core = GetModuleHandleA("Qt5Core.dll")) {
        if (const auto addr = GetProcAddress(hQt5Core, kQObjectConnectCharSymbol)) {
            s_qobjectConnectCharDetour = new PLH::x64Detour(
                reinterpret_cast<uint64_t>(addr),
                reinterpret_cast<uint64_t>(&hookQObjectConnectChar),
                &s_qobjectConnectCharOriginal);
            s_qobjectConnectCharDetour->hook();
            LOG_INFO("QObject::connect(char*) hook installed (SIGNAL/SLOT macros covered)");
        } else {
            LOG_CRITICAL("QObject::connect(char*) symbol not found in Qt5Core.dll");
        }
    }

    // ── QObject::connect(QMetaMethod) hook ────────────────────────────────────
    // Covers connections made with pre-resolved QMetaMethod objects (A75).
    // Goes through internal 0x1CC300 — never touches A7A or A76.
    constexpr const char* kQObjectConnectMetaMethodSymbol =
        "?connect@QObject@@SA?AVConnection@QMetaObject@@PEBV1@AEBVQMetaMethod@@01W4ConnectionType@Qt@@@Z";

    if (const HMODULE hQt5Core = GetModuleHandleA("Qt5Core.dll")) {
        if (const auto addr = GetProcAddress(hQt5Core, kQObjectConnectMetaMethodSymbol)) {
            s_qobjectConnectMetaMethodDetour = new PLH::x64Detour(
                reinterpret_cast<uint64_t>(addr),
                reinterpret_cast<uint64_t>(&hookQObjectConnectMetaMethod),
                &s_qobjectConnectMetaMethodOriginal);
            s_qobjectConnectMetaMethodDetour->hook();
            LOG_INFO("QObject::connect(QMetaMethod) hook installed (meta-method connections covered)");
        } else {
            LOG_CRITICAL("QObject::connect(QMetaMethod) symbol not found in Qt5Core.dll");
        }
    }

    // ── QMetaObject::connectSlotsByName hook: setupUi() auto-connections ─────
    // connectSlotsByName() bypasses both QObjectPrivate::connectImpl and
    // QMetaObject::connect, calling internal non-exported helpers directly.
    // Hooking the exported entry point is the only way to observe these.
    constexpr const char* kConnectSlotsByNameSymbol =
        "?connectSlotsByName@QMetaObject@@SAXPEAVQObject@@@Z";

    if (const HMODULE hQt5Core = GetModuleHandleA("Qt5Core.dll")) {
        if (const auto addr = GetProcAddress(hQt5Core, kConnectSlotsByNameSymbol)) {
            s_connectSlotsByNameDetour = new PLH::x64Detour(
                reinterpret_cast<uint64_t>(addr),
                reinterpret_cast<uint64_t>(&hookConnectSlotsByName),
                &s_connectSlotsByNameOriginal);
            s_connectSlotsByNameDetour->hook();
            LOG_INFO("connectSlotsByName hook installed (setupUi auto-connections covered)");
        } else {
            LOG_CRITICAL("connectSlotsByName symbol not found in Qt5Core.dll");
        }
    }

    HooksManager::addBefore<&QNetworkAccessManager::get>([&](HookHandle, QNetworkAccessManager *&, const QNetworkRequest & request) {
        LOG_INFO("Get request");
    });

    // ── QMetaObject::activate hooks: intercept every signal emission ──────────
    // Symbols confirmed from Qt5Core.dll PE export table.
    struct { const char* sym; uint64_t* original; void* hook; PLH::x64Detour** detour; const char* label; } activateHooks[] = {
        {
            "?activate@QMetaObject@@SAXPEAVQObject@@PEBU1@HPEAPEAX@Z",
            &s_activateMOCOriginal, reinterpret_cast<void*>(&hookActivateMOC),
            &s_activateMOCDetour, "activate(MOC)"
        },
        {
            "?activate@QMetaObject@@SAXPEAVQObject@@HPEAPEAX@Z",
            &s_activateLegacyOriginal, reinterpret_cast<void*>(&hookActivateLegacy),
            &s_activateLegacyDetour, "activate(legacy)"
        },
        {
            "?activate@QMetaObject@@SAXPEAVQObject@@HHPEAPEAX@Z",
            &s_activateRangeOriginal, reinterpret_cast<void*>(&hookActivateRange),
            &s_activateRangeDetour, "activate(range)"
        },
    };

    if (const HMODULE hQt5Core = GetModuleHandleA("Qt5Core.dll")) {
        for (auto& h : activateHooks) {
            if (const auto addr = GetProcAddress(hQt5Core, h.sym)) {
                *h.detour = new PLH::x64Detour(
                    reinterpret_cast<uint64_t>(addr),
                    reinterpret_cast<uint64_t>(h.hook),
                    h.original);
                (*h.detour)->hook();
                LOG_INFO("{} hook installed", h.label);
            } else {
                LOG_CRITICAL("{} symbol not found in Qt5Core.dll", h.label);
            }
        }
    }

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

        QMetaObject::invokeMethod(test, "LoginSucceed", Q_ARG(QString, "hello"));

        for (const auto& widget: QApplication::allWidgets()) {

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

    HooksManager::addBefore<&QSettings::beginGroup>(
        [&](const HookHandle handle, QSettings *settings, const QString &prefix) {
            LOG_DEBUG("Begin group {}", prefix.toStdString());
        });
    HooksManager::addBefore<&QSettings::endGroup>(
        [](const HookHandle handle, QSettings *settings) {
            LOG_DEBUG("End group");
        });

    HooksManager::addAfter<&QSettings::value>(
    [](const HookHandle& handle, QVariant& ret, const QSettings*& settings, const QString& key, const QVariant& defaultValue) {
        LOG_DEBUG("QSettings::value: key={} value={}", key.toStdString(), ret.toString().toStdString());
    });

    HooksManager::addBefore<&QSettings::setValue>(
    [](const HookHandle& handle, QSettings*& settings, const QString &key, const QVariant &value) {
        LOG_DEBUG("QSettings::setValue: key={} value={}", key.toStdString(), value.toString().toStdString());
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

#include "ExtensionsManager.moc"