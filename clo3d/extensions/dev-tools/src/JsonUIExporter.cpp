#include "JsonUIExporter.h"

JsonUIExporter::JsonUIExporter(JsonUIExporterOptions *options): options_(options) {}

JsonUIExporter::~JsonUIExporter() {
    delete options_;
}

void JsonUIExporter::exportUI() {
}
