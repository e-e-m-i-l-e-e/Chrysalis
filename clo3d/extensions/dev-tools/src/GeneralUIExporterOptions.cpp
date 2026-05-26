#include "GeneralUIExporterOptions.h"

#include <QKeySequence>

#include "Logging.h"
#define LOGGER_NAME "UI Exporter Options"

void GeneralUIExporterOptions::read(const QSettings* settings) {
    BaseUIExporterOptions::read(settings);
    setShortcut(settings->value(Keys::SHORTCUT, Defaults::SHORTCUT).value<QKeySequence>());
    setPickMyMouse(settings->value(Keys::PICK_BY_MOUSE, Defaults::PICK_BY_MOUSE).toBool());
}

void GeneralUIExporterOptions::write(QSettings* settings) {
    BaseUIExporterOptions::write(settings);
    settings->setValue(Keys::SHORTCUT, shortcut_);
    settings->setValue(Keys::PICK_BY_MOUSE, pickByMouse_);
}

QKeySequence GeneralUIExporterOptions::getShortcut() const {
    return shortcut_;
}

bool GeneralUIExporterOptions::getPickMyMouse() const {
    return pickByMouse_;
}

void GeneralUIExporterOptions::setShortcut(const QKeySequence &shortcut) {
    shortcut_ = shortcut;
    shortcutHandler_->setShortcut(shortcut_);
}

void GeneralUIExporterOptions::setPickMyMouse(bool pickByMouse) {
    pickByMouse_ = pickByMouse;
}

void GeneralUIExporterOptions::setShortcutHandler(BaseNativeShortcutHandler* shortcutHandler) {
    shortcutHandler_ = shortcutHandler;
}
