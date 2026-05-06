#include "UIExporterTool.h"

#include "UIExporterToolSettings.h"
#include "UIExporterToolSettingsWidget.h"

UIExporterTool::UIExporterTool(UIExporterToolSettings *uiExporterToolSettings, GeneralUIExporterOptions *options)
    : BaseNativeShortcutHandler(options->getShortcut()), options_(options), uiExporterToolSettings_(uiExporterToolSettings) {
    uiExporterToolSettings_->addOptions(options);
}

UIExporterTool::~UIExporterTool() {
    delete options_;
    delete uiExporterToolSettings_;
}

void UIExporterTool::configureSettings(ExtensionsSettings *extensionsSettings) {
    extensionsSettings->addSettings(uiExporterToolSettings_);
}

void UIExporterTool::configureSettingsUI(UI::ExtensionsSettingsDialog *extensionsSettingsDialog) {
    extensionsSettingsDialog->addPage(
        new UI::UIExporterToolSettingsWidget(uiExporterToolSettings_, extensionsSettingsDialog));
}

void UIExporterTool::addExporter(BaseUIExporter *exporter) {
    exporters_.push_front(exporter);
    uiExporterToolSettings_->addOptions(exporter->getOptions());
}

void UIExporterTool::handle() {
    for (const auto exporter : exporters_) {
        exporter->exportUI();
    }
}