#include "GeneralUIExporterOptions.h"

#include <QKeySequence>

GeneralUIExporterOptions::GeneralUIExporterOptions(const QSettings* settings)
    : BaseUIExporterOptions(settings) {}

QKeySequence GeneralUIExporterOptions::getShortcut() const {
    return QKeySequence("Ctrl+Shift+E");
}

bool GeneralUIExporterOptions::getPickMyMouse() const {
    return true;
}