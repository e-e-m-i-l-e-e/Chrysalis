#include "UIExporterTool.h"

UIExporterTool::UIExporterTool(GeneralUIExporterOptions* options): options_(options) {}

UIExporterTool::~UIExporterTool() {
    delete options_;
}

void UIExporterTool::addExporter(BaseUIExporter* exporter) {
    exporters_.push_front(exporter);
}

void UIExporterTool::setSettings(const BaseExtensionsSettingsEditor *settingsEditor) {
    BaseExtensionsSettingsPage::setSettings(settingsEditor);
    for (const auto& exporter : exporters_) {
        exporter->setSettings(settingsEditor);
    }
}

void UIExporterTool::readSettings() {
    const auto settings = editSettings(typeid(this).name());
    options_->read(settings);
}
