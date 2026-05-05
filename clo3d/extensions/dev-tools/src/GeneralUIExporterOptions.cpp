#include "GeneralUIExporterOptions.h"

#include <QKeySequence>

void GeneralUIExporterOptions::read(const Settings &settings) {
    BaseUIExporterOptions::read(settings);
    shortcut_ = settings.value(Keys::SHORTCUT, Defaults::SHORTCUT).value<QKeySequence>();
    pickByMouse_ = settings.value(Keys::PICK_BY_MOUSE, Defaults::PICK_BY_MOUSE).toBool();
}

QKeySequence GeneralUIExporterOptions::getShortcut() const {
    return shortcut_;
}

bool GeneralUIExporterOptions::getPickMyMouse() const {
    return pickByMouse_;
}

void GeneralUIExporterOptions::setShortcut(const Settings &settings, const QKeySequence &shortcut) {
    settings.setValue(Keys::SHORTCUT, shortcut);
    shortcut_ = shortcut;
}

void GeneralUIExporterOptions::setPickMyMouse(const Settings &settings, bool pickByMouse) {
    settings.setValue(Keys::PICK_BY_MOUSE, pickByMouse_);
    pickByMouse_ = pickByMouse;
}