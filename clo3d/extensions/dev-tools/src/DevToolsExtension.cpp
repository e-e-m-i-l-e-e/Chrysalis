#include "DevToolsExtension.h"

#include "UIExporterTool.h"

#include "XmlUIExporter.h"
#include "JsonUIExporter.h"

#include "JsonUIExporterOptions.h"
#include "XmlUIExporterOptions.h"

void DevToolsExtension::install() {
    const auto generalUIExporterOptions = new GeneralUIExporterOptions();
    uiExporterTool = new UIExporterTool(generalUIExporterOptions);

    const auto jsonUIExporterOptions = new JsonUIExporterOptions();
    const auto jsonUIExporter = new JsonUIExporter(jsonUIExporterOptions);
    uiExporterTool->addExporter(jsonUIExporter);

    const auto xmlUIExporterOptions = new XmlUIExporterOptions();
    const auto xmlUIExporter = new XmlUIExporter(xmlUIExporterOptions);
    uiExporterTool->addExporter(xmlUIExporter);
}

void DevToolsExtension::configureSettings(ExtensionsSettings* extensionsSettings) {
    extensionsSettings->addSettings(uiExporterTool);
}
