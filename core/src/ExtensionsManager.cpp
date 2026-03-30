#include "ExtensionsManager.h"

#define LOGGER_NAME "Extensions Manager"

#include <windows.h>
#include <QApplication>
#include <QMenuBar>
#include <QMetaMethod>

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

// ── QMetaObject::connect hook infrastructure ──────────────────────────────────
// Old-style SIGNAL/SLOT connections (connect(sender, SIGNAL(...), SLOT(...)))
// do NOT go through QObjectPrivate::connectImpl. They resolve the char* strings
// to integer indices and call QMetaObject::connect(sender, signalIdx, receiver,
// slotIdx, type, types) — a completely separate code path.
//
// Hooking this function catches every old-style connection.
// signalIdx / slotIdx are absolute method indices on the sender/receiver metaobject.
//
// Symbol confirmed from .misc/Qt5Core:
//   ?connect@QMetaObject@@SA?AVConnection@1@PEBVQObject@@H0HHPEAH@Z
//   QMetaObject::connect(const QObject*, int, const QObject*, int, int, int*)
using QMetaObjectConnectFn = QMetaObject::Connection(*)(
    const QObject*, int,
    const QObject*, int,
    int, int*);

static uint64_t        s_metaObjectConnectOriginal = 0;
static PLH::x64Detour* s_metaObjectConnectDetour   = nullptr;

static QMetaObject::Connection hookQMetaObjectConnect(
    const QObject* sender,   int signalIndex,
    const QObject* receiver, int slotIndex,
    int type, int* types)
{
    if (sender && receiver) {
        if (!QString(sender->metaObject()->className()).startsWith("Q") || !QString(receiver->metaObject()->className()).startsWith("Q")) {
            const QMetaMethod signal = sender->metaObject()->method(signalIndex);
            LOG_DEBUG("connect(old-style)  {}({})::{}  →  {}({})",
                sender->metaObject()->className(),
                sender->objectName().toStdString(),
                signal.methodSignature().constData(),
                receiver->metaObject()->className(),
                receiver->objectName().toStdString());
        }
    }
    return reinterpret_cast<QMetaObjectConnectFn>(s_metaObjectConnectOriginal)(
        sender, signalIndex, receiver, slotIndex, type, types);
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
            LOG_DEBUG("connectImpl  {}({}) ::{}  →  {}({})",
                sender->metaObject()->className(),
                sender->objectName().toStdString(),
                signal.methodSignature().constData(),
                receiver ? receiver->metaObject()->className() : "<nullptr>",
                receiver ? receiver->objectName().toStdString() : "<nullptr>");
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

// Primary MOC-generated path — resolves the signal name from m + local index.
static void hookActivateMOC(QObject* sender, const QMetaObject* m, int localIdx, void** argv)
{
    if (sender && m && !QString(sender->metaObject()->className()).startsWith("Q")) {
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
    // Does NOT cover old-style SIGNAL/SLOT macros — see QMetaObject::connect hook below.

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

    // ── QMetaObject::connect hook: old-style SIGNAL/SLOT connections ──────────
    // connect(sender, SIGNAL(foo()), receiver, SLOT(bar())) resolves strings to
    // integer indices and calls QMetaObject::connect(int, int) — never touches
    // QObjectPrivate::connectImpl. This hook closes that gap.
    constexpr const char* kMetaObjectConnectSymbol =
        "?connect@QMetaObject@@SA?AVConnection@1@PEBVQObject@@H0HHPEAH@Z";

    if (const HMODULE hQt5Core = GetModuleHandleA("Qt5Core.dll")) {
        if (const auto addr = GetProcAddress(hQt5Core, kMetaObjectConnectSymbol)) {
            s_metaObjectConnectDetour = new PLH::x64Detour(
                reinterpret_cast<uint64_t>(addr),
                reinterpret_cast<uint64_t>(&hookQMetaObjectConnect),
                &s_metaObjectConnectOriginal);
            s_metaObjectConnectDetour->hook();
            LOG_INFO("QMetaObject::connect hook installed (old-style SIGNAL/SLOT covered)");
        } else {
            LOG_CRITICAL("QMetaObject::connect symbol not found in Qt5Core.dll");
        }
    }

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

    HooksManager::addBefore<&QApplication::exec>([&](const HookHandle &handle) {

        QMenuBar* menu = nullptr;

        for (const auto widget: QApplication::allWidgets()) {
            // Configure main window
            if (widget->objectName() == "TitleFrame") {
                mainWindow = dynamic_cast<QFrame*>(widget);
                LOG_INFO("Main window has been detected by Extensions Manager.");
            }

            // Getting menu bar for further configuration
            else if (widget->objectName() == "myMenuBar") menu = qobject_cast<QMenuBar*>(widget);

            // Inject QLabel for displaying messages from background processes into bottom status bar.
            else if (QString(widget->metaObject()->className()) == "MVStatusBar") {
                for (const auto statusBar = dynamic_cast<MVStatusBar*>(widget);
                     const auto child: statusBar->children()) {
                    if (child->metaObject() == &QWidget::staticMetaObject && !child->children().empty()) {
                        const auto parent = qobject_cast<QWidget*>(child);
                        backgroundMessage_ = new QLabel(parent);
                        backgroundMessage_->setGeometry(statusBar->width() / 2, 2, 500, 20);
                        UTILITY_API->UpdateCloStyleForPlugIn(backgroundMessage_);
                        backgroundMessage_->show();

                        for (const auto extension: extensions) {
                            extension->configureStatusBar(parent);
                        }
                    }
                }
            }

            for (const auto extension: extensions) {
                extension->configure(widget);
            }
        }

        if (!menu) {
            LOG_CRITICAL("Menu was not found");
            exit(1);
        }

        // Configuring menu
        const auto extensionsMenu = menu->addMenu("Extensions");

        extensionsSettings = new ExtensionsSettings(mainWindow);
        const QAction *extensionsSettingsMenu = extensionsMenu->addAction("Extensions Settings");
        QObject::connect(extensionsSettingsMenu, &QAction::triggered, extensionsSettings, &ExtensionsSettings::exec);

        for (const auto extension: extensions) {
            extension->configureMenu(extensionsMenu);
        }

        LOG_INFO("Extensions menu has been added to myMenuBar");
        handle.remove();
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