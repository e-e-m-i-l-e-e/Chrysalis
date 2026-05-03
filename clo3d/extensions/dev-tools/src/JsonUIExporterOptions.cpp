#include "JsonUIExporterOptions.h"

JsonUIExporterOptions::JsonUIExporterOptions(): BaseUIExporterOptions() {}

bool JsonUIExporterOptions::getVisibleOnly(Settings& settings) const {
    return true;
}

bool JsonUIExporterOptions::getIgnoreCSS(Settings& settings) const {
    return true;
}
