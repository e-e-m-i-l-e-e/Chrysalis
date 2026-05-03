#include "GeneralUIExporterOptions.h"

#include <QKeySequence>

GeneralUIExporterOptions::GeneralUIExporterOptions(): BaseUIExporterOptions() {}

QKeySequence GeneralUIExporterOptions::getShortcut(Settings& settings) const {
    return QKeySequence("Ctrl+Shift+E");
}

bool GeneralUIExporterOptions::getPickMyMouse(Settings& settings) const {
    return true;
}