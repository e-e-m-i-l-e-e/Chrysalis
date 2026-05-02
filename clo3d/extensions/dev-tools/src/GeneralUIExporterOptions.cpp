#include "GeneralUIExporterOptions.h"

#include <QKeySequence>

GeneralUIExporterOptions::GeneralUIExporterOptions(): BaseUIExporterOptions() {}

QKeySequence GeneralUIExporterOptions::getShortcut(QSettings* settings) const {
    return QKeySequence("Ctrl+Shift+E");
}

bool GeneralUIExporterOptions::getPickMyMouse(QSettings* settings) const {
    return true;
}