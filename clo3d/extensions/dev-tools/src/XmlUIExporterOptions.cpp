#include "XmlUIExporterOptions.h"

XmlUIExporterOptions::XmlUIExporterOptions(): BaseUIExporterOptions() {}

bool XmlUIExporterOptions::getExportIcons(Settings& settings) const {

    return true;
}

bool XmlUIExporterOptions::getUICompatible(Settings& settings) const {
    return true;
}
