#include "JsonUIExporterOptions.h"

JsonUIExporterOptions::JsonUIExporterOptions(const QSettings* settings)
    : BaseUIExporterOptions(settings) {}

bool JsonUIExporterOptions::getVisibleOnly() const {
    return true;
}

bool JsonUIExporterOptions::getIgnoreCSS() const {
    return true;
}
