#include "UIExporterTool.h"

#include <iostream>

#include "UIExporterToolSettings.h"
#include "UIExporterToolSettingsWidget.h"

UIExporterTool::UIExporterTool(UIExporterToolSettings* uiExporterToolSettings, GeneralUIExporterOptions *options)
    : uiExporterToolSettings_(uiExporterToolSettings), options_(options) {
    uiExporterToolSettings_->addOptions(options);
}

UIExporterTool::~UIExporterTool() {
    delete options_;
    delete uiExporterToolSettings_;
}

void UIExporterTool::configureSettings(ExtensionsSettings *extensionsSettings) {
    extensionsSettings->addSettings(uiExporterToolSettings_);
}

void UIExporterTool::configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) {
    extensionsSettingsDialog->addPage(new UI::UIExporterToolSettingsWidget(uiExporterToolSettings_, extensionsSettingsDialog));
}

void UIExporterTool::addExporter(BaseUIExporter* exporter) {
    exporters_.push_front(exporter);
    uiExporterToolSettings_->addOptions(exporter->getOptions());
}

// void UIExporterTool::setSettings(const BaseExtensionsSettingsEditor *settingsEditor) {
//     BaseExtensionsSettingsPage::setSettings(settingsEditor);
//     for (const auto& exporter : exporters_) {
//         exporter->setSettings(settingsEditor);
//     }
// }
//
// void UIExporterTool::readSettings() {
//     const auto settings = editSettings(typeid(this).name());
//     options_->read(settings);
// }
