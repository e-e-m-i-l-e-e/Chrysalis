#include "BaseNativeShortcutHandler.h"

#include <Windows.h>
#include <unordered_map>

#include "Logger.h"
#define LOGGER_NAME "Shortcut Handler"

// TODO: class for statics
static int nextId = 1;
static std::unordered_map<int, BaseNativeShortcutHandler*> registry;
HHOOK listenerHook = nullptr;

LRESULT nativeEventHandler(const int nCode, const WPARAM wParam, const LPARAM lParam) {
    if (nCode == HC_ACTION) {
        const MSG* msg = reinterpret_cast<MSG*>(lParam);
        if (msg->message == WM_HOTKEY) {
            BaseNativeShortcutHandler::getEventHandler(msg->wParam)->handle();
        }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

BaseNativeShortcutHandler::BaseNativeShortcutHandler(const QKeySequence &shortcut): id_(nextId++), shortcut_(shortcut) {
    registry[id_] = this;
}

BaseNativeShortcutHandler::~BaseNativeShortcutHandler() {
    registry.erase(id_);
    UnregisterHotKey(nullptr, id_);
}

BaseNativeShortcutHandler* BaseNativeShortcutHandler::getEventHandler(const int id) {
    return registry[id];
}

void BaseNativeShortcutHandler::stopListening() {
    UnhookWindowsHookEx(listenerHook);
}

void BaseNativeShortcutHandler::startListening() {
    listenerHook = SetWindowsHookEx(WH_GETMESSAGE, &nativeEventHandler, nullptr, GetCurrentThreadId());
}

void BaseNativeShortcutHandler::registerShortcuts() {
    for (const auto &handler: registry | std::views::values) {
        handler->registerShortcut();
    }
}

void BaseNativeShortcutHandler::setShortcut(const QKeySequence &shortcut) {
    shortcut_ = shortcut;
    registerShortcut();
}

void BaseNativeShortcutHandler::registerShortcut() const {
    const auto key = shortcut_[0] & ~Qt::KeyboardModifierMask & 0xFFFF;;
    const auto qtModifiers = shortcut_[0] & Qt::KeyboardModifierMask;

    UINT winModifiers = 0;
    if (qtModifiers & Qt::ControlModifier) winModifiers |= MOD_CONTROL;
    if (qtModifiers & Qt::ShiftModifier)   winModifiers |= MOD_SHIFT;
    if (qtModifiers & Qt::AltModifier)     winModifiers |= MOD_ALT;
    if (qtModifiers & Qt::MetaModifier)    winModifiers |= MOD_WIN;

    UnregisterHotKey(nullptr, id_);
    if (!RegisterHotKey(nullptr, id_, winModifiers, key)) {
        LOG_ERROR("Shortcut registration failed: {}", GetLastError());
    }
}
