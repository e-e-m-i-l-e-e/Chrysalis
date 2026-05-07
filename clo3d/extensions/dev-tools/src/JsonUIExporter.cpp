#include "JsonUIExporter.h"

JsonUIExporter::JsonUIExporter(JsonUIExporterOptions *options): options_(options) {}

JsonUIExporter::~JsonUIExporter() {
    delete options_;
}

void JsonUIExporter::exportUI() {
}

void JsonUIExporter::exportUI(QWidget *widget) {
}

void JsonUIExporter::exportUI(std::forward_list<QWidget *> widgets) {
}

BaseUIExporterOptions* JsonUIExporter::getOptions() {
    return options_;
}
