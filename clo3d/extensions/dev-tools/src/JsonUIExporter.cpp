#include "JsonUIExporter.h"

JsonUIExporter::JsonUIExporter(JsonUIExporterOptions *options): options_(options) {}

JsonUIExporter::~JsonUIExporter() {
    delete options_;
}

void JsonUIExporter::exportUI() {
}

BaseUIExporterOptions* JsonUIExporter::getOptions() {
    return options_;
}
