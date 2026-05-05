#include "XmlUIExporter.h"

XmlUIExporter::XmlUIExporter(XmlUIExporterOptions *options): options_(options) {}

XmlUIExporter::~XmlUIExporter() {
    delete options_;
}

void XmlUIExporter::exportUI() {
}

BaseUIExporterOptions* XmlUIExporter::getOptions() {
    return options_;
}
