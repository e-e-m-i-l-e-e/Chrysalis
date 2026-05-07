#include "UIExporterTool.h"

#include <unordered_map>

#include <QApplication>

#include "UIExporterToolSettings.h"
#include "UIExporterToolSettingsWidget.h"

#include "Logger.h"
#define LOGGER_NAME "UI Exporter"

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
    QWidget* widgetAtMousePosition = nullptr;
    if (options_->getPickMyMouse()) {
        widgetAtMousePosition = QApplication::widgetAt(QCursor::pos());
        LOG_DEBUG("Exporting widget at cursor position. Class name: {}. Object name: {}.",
                  widgetAtMousePosition->metaObject()->className(),
                  widgetAtMousePosition->objectName().toStdString()
        );
    }
    std::unordered_map<QString, std::unordered_map<QString, std::forward_list<QWidget*>>> foundWidgets; // <className, <objectName, widgets>>
    for (const auto exporter : exporters_) {
        const auto options = exporter->getOptions();
        if (!options->isEnabled()) {
            LOG_DEBUG("Skipping export using {}", typeid(*exporter).name());
            continue;
        }
        if (widgetAtMousePosition) {
            exporter->exportUI(widgetAtMousePosition);
        } else if (options->getClassName().isEmpty() && options->getObjectName().isEmpty()) {
            // There are no common arguments passed. Let UI Exporter implementation to decide what to export.
            exporter->exportUI();
        } else {
            const QString& className = options->getClassName();
            const QString& objectName = options->getObjectName();
            for (const auto widget: QApplication::allWidgets()) {
                if ((objectName.isEmpty() || objectName == widget->objectName()) &&
                    (className.isEmpty() || className == widget->metaObject()->className())) {
                    LOG_DEBUG(
                        "Matching widget has been found with class \"{}\" and name \"{}\"",
                        widget->metaObject()->className(),
                        widget->objectName().toStdString()
                    );
                    foundWidgets[className][objectName].push_front(widget);
                }
            }
            exporter->exportUI(foundWidgets[className][objectName]);
        }
    }
}