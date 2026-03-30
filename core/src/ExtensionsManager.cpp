#include "ExtensionsManager.h"

#define LOGGER_NAME "Extensions Manager"

#include <windows.h>
#include <QApplication>
#include <QMenuBar>
#include <QMetaMethod>

#include "ExtensionsSettings.h"

#include "HooksManager.h"
#include "MVStatusBar.h"

// ── connectImpl static hook infrastructure ────────────────────────────────────
// QObject::connectImpl is private but exported from Qt5Core.dll.
// All new-style connect() template overloads (pointer-to-member, functor) funnel
// into this single function, so one hook here covers every new-style connection.
//
// Because the member is private, &QObject::connectImpl is inaccessible at compile
// time. The address must be resolved at runtime via GetProcAddress.
//
// Mangled symbol confirmed via PE export table inspection of Qt5Core.dll:
//   ?connectImpl@QObject@@CA?AVConnection@QMetaObject@@PEBV1@PEAPEAX01
//   PEAVQSlotObjectBase@QtPrivate@@W4ConnectionType@Qt@@PEBHPEBU3@@Z
//
// QSlotObjectBase is forward-declared because we only pass the pointer through
// without dereferencing — the full definition is not needed here.
namespace QtPrivate { class QSlotObjectBase; }

using ConnectImplFn = QMetaObject::Connection(*)(
    const QObject*, void**,
    const QObject*, void**,
    QtPrivate::QSlotObjectBase*, Qt::ConnectionType,
    const int*, const QMetaObject*);

static uint64_t        s_connectImplOriginal = 0;
static PLH::x64Detour* s_connectImplDetour   = nullptr;

static QMetaObject::Connection hookConnectImpl(
    const QObject* sender,   void** signal,
    const QObject* receiver, void** slotPtr,
    QtPrivate::QSlotObjectBase* slot, Qt::ConnectionType type,
    const int* types, const QMetaObject* senderMeta)
{
    if (receiver->objectName() == "mvdockingButton" || QStringList({"CloUICommon::Accordion", "CloUICommon::ImageLabel"}).contains(receiver->metaObject()->className())) {
        LOG_DEBUG("connectImpl  sender={}  receiver={}  meta={}",
                  sender ? sender->metaObject()->className() : "<null>",
                  receiver ? receiver->metaObject()->className() : "<null>",
                  senderMeta ? senderMeta->className() : "<null>");
    }

    return reinterpret_cast<ConnectImplFn>(s_connectImplOriginal)(
        sender, signal, receiver, slotPtr, slot, type, types, senderMeta);
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

// Primary MOC-generated path — resolves the signal name from m + local index.
static void hookActivateMOC(QObject* sender, const QMetaObject* m, int localIdx, void** argv)
{
    if (sender && m) {
        const int absIdx = m->methodOffset() + localIdx;
        const QMetaMethod sig = sender->metaObject()->method(absIdx);
        LOG_DEBUG("emit  {}({})::{}",
            sender->metaObject()->className(),
            sender->objectName().toStdString(),
            sig.methodSignature().constData());
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
    if (sender) {
        const QMetaMethod sig = sender->metaObject()->method(fromIdx);
        LOG_DEBUG("emit(range {}-{})  {}({})::{}",
            fromIdx, toIdx,
            sender->metaObject()->className(),
            sender->objectName().toStdString(),
            sig.methodSignature().constData());
    }
    reinterpret_cast<ActivateRangeFn>(s_activateRangeOriginal)(sender, fromIdx, toIdx, argv);
}

void ExtensionsManager::registerExtension(Extension *extension) {
    extensions.push_back(extension);
}

void ExtensionsManager::install() {
    // QObject::connect has multiple overloads in Qt5 (string-based, QMetaMethod-based,
    // and several functor templates). We must disambiguate explicitly; otherwise
    // `&QObject::connect` is ambiguous and the compiler rejects it.
    // We target the classic string-based (Qt4-style) overload because it is the one
    // CLO internally uses for most of its own signal wiring.
    using ConnectFn = QMetaObject::Connection(*)(
        const QObject *, const char *,
        const QObject *, const char *,
        Qt::ConnectionType);
    constexpr ConnectFn qObjectConnect =
        static_cast<ConnectFn>(&QObject::connect);

    // HooksManager passes every argument as T& — the lambda must accept references.
    // This also lets a Before callback redirect sender/receiver/signal at intercept time.
    HooksManager::addBefore<qObjectConnect>([](
        const HookHandle & /*handle*/,
        const QObject *&sender,   const char *&signal,
        const QObject *&receiver, const char *&member,
        Qt::ConnectionType & /*type*/) {
            if (receiver->objectName() == "mvdockingButton" || QStringList({"CloUICommon::Accordion", "CloUICommon::ImageLabel"}).contains(receiver->metaObject()->className())) {
                LOG_DEBUG("QObject::connect(char*)  {}::{}  →  {}::{}",
                          sender ? sender->metaObject()->className() : "<null>", signal ? signal : "<null>",
                          receiver ? receiver->metaObject()->className() : "<null>", member ? member : "<null>");
            }
    });

    // ── Overload 2: QMetaMethod-based static connect ──────────────────────────
    // connect(const QObject*, const QMetaMethod&, const QObject*, const QMetaMethod&,
    //         Qt::ConnectionType)
    // Used internally by Qt's own meta-system when it resolves signals at runtime
    // (e.g. QMetaObject::activate, QSignalSpy). Not commonly called by user code
    // directly but is the path taken by Qt when two QMetaMethod handles are known.
    using ConnectMetaFn = QMetaObject::Connection(*)(
        const QObject *, const QMetaMethod &,
        const QObject *, const QMetaMethod &,
        Qt::ConnectionType);
    constexpr ConnectMetaFn qObjectConnectMeta =
        static_cast<ConnectMetaFn>(&QObject::connect);

    HooksManager::addBefore<qObjectConnectMeta>([](
        const HookHandle & /*handle*/,
        const QObject *&sender,   const QMetaMethod &signal,
        const QObject *&receiver, const QMetaMethod &method,
        Qt::ConnectionType & /*type*/) {
            if (receiver->objectName() == "mvdockingButton" || QStringList({"CloUICommon::Accordion", "CloUICommon::ImageLabel"}).contains(receiver->metaObject()->className())) {
                LOG_DEBUG("QObject::connect(QMetaMethod)  {}::{}  →  {}::{}",
                          sender ? sender->metaObject()->className() : "<null>", signal.name().constData(),
                          receiver ? receiver->metaObject()->className() : "<null>", method.name().constData());
            }
    });

    // ── Overloads NOT hooked and why ──────────────────────────────────────────
    //
    // Overload 3 — inline non-static const:
    //   connect(const QObject*, const char*, const char*, ConnectionType) const
    //   This is an inline wrapper defined entirely in qobject.h that just calls
    //   overload 1 (the char* static). It has no independent address in Qt5Core.dll
    //   and is already caught by the hook above.
    //
    // Template overloads (new-style signal/slot):
    //   connect(sender, &Foo::signal, receiver, &Bar::slot, ...)
    //   connect(sender, &Foo::signal, functor, ...)
    //   These are inline function templates in qobject.h; they do not compile to
    //   a single exportable symbol. All of them funnel into the protected static
    //   QObject::connectImpl(). Because connectImpl is protected, it cannot be
    //   addressed from external code via &QObject::connectImpl. To hook new-style
    //   connections, resolve connectImpl's address at runtime via GetProcAddress
    //   on Qt5Core.dll and install a raw PolyHook detour manually.

    // ── connectImpl hook: covers all new-style template connect() overloads ──
    // Symbol confirmed from Qt5Core.dll PE export table.
    constexpr const char* kConnectImplSymbol =
        "?connectImpl@QObject@@CA?AVConnection@QMetaObject@@PEBV1@PEAPEAX01"
        "PEAVQSlotObjectBase@QtPrivate@@W4ConnectionType@Qt@@PEBHPEBU3@@Z";

    if (const HMODULE hQt5Core = GetModuleHandleA("Qt5Core.dll")) {
        if (const auto addr = GetProcAddress(hQt5Core, kConnectImplSymbol)) {
            s_connectImplDetour = new PLH::x64Detour(
                reinterpret_cast<uint64_t>(addr),
                reinterpret_cast<uint64_t>(&hookConnectImpl),
                &s_connectImplOriginal);
            s_connectImplDetour->hook();
            LOG_INFO("connectImpl hook installed (new-style signals covered)");
        } else {
            LOG_CRITICAL("connectImpl symbol not found in Qt5Core.dll — new-style connections will not be intercepted");
        }
    } else {
        LOG_CRITICAL("Qt5Core.dll not loaded — connectImpl hook skipped");
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
