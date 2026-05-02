#include "XmlUIExporterOptions.h"

XmlUIExporterOptions::XmlUIExporterOptions(): BaseUIExporterOptions() {}

bool XmlUIExporterOptions::getExportIcons(QSettings* settings) const {
    return true;
}

bool XmlUIExporterOptions::getUICompatible(QSettings* settings) const {
    return true;
}
