#include "JsonUIExporterOptions.h"

JsonUIExporterOptions::JsonUIExporterOptions(): BaseUIExporterOptions() {}

bool JsonUIExporterOptions::getVisibleOnly(QSettings* settings) const {
    return true;
}

bool JsonUIExporterOptions::getIgnoreCSS(QSettings* settings) const {
    return true;
}
