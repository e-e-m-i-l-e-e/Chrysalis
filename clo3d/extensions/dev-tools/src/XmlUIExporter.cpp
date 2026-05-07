#include "XmlUIExporter.h"

XmlUIExporter::XmlUIExporter(XmlUIExporterOptions *options): options_(options) {}

XmlUIExporter::~XmlUIExporter() {
    delete options_;
}

void XmlUIExporter::exportUI() {
}

void XmlUIExporter::exportUI(QWidget *widget) {
}

void XmlUIExporter::exportUI(std::forward_list<QWidget *> widgets) {
}

BaseUIExporterOptions* XmlUIExporter::getOptions() {
    return options_;
}
