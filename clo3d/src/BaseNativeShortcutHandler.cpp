#include "BaseNativeShortcutHandler.h"

#include <unordered_map>

#include "Logger.h"

#define LOGGER_NAME "Shortcut Handler"

static int nextId = 1;
static inline std::unordered_map<int, BaseNativeShortcutHandler*> registry;

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
