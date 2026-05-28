#include "UIExporterTool.h"

#include <unordered_map>

#include <QApplication>

#include "XmlUIExporter.h"
#include "JsonUIExporter.h"
#include "ExtensionsManager.h"
#include "UIExporterToolSettings.h"
#include "UIExporterToolSettingsWidget.h"

#include "Logging.h"
#define LOGGER_NAME "UI Exporter"

UIExporterTool::UIExporterTool(UIExporterToolSettings *uiExporterToolSettings, GeneralUIExporterOptions *options)
    : BaseNativeShortcutHandler(options->getShortcut()), options_(options), uiExporterToolSettings_(uiExporterToolSettings) {
    uiExporterToolSettings_->addOptions(options);
    options_->setShortcutHandler(this);
}

UIExporterTool::~UIExporterTool() {
    delete options_;
    delete uiExporterToolSettings_;
}

UIExporterTool* UIExporterTool::create() {
    const auto uiExporterTool = new UIExporterTool(new UIExporterToolSettings(), new GeneralUIExporterOptions());
    uiExporterTool->addExporter(JsonUIExporter::create());
    uiExporterTool->addExporter(XmlUIExporter::create());
    return uiExporterTool;
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
        static constexpr auto LOG_EXPORT_AT_CURSOR = "Exporting widget at cursor position. Class name: {}. Object name: {}.";
        LOG_DEBUG(LOG_EXPORT_AT_CURSOR, widgetAtMousePosition->metaObject()->className(), widgetAtMousePosition->objectName().toStdString()
        );
    }
    std::unordered_map<QString, std::unordered_map<QString, std::forward_list<QWidget*>>> foundWidgets; // <className, <objectName, widgets>>
    for (const auto exporter : exporters_) {
        const auto options = exporter->getOptions();
        if (!options->isEnabled()) {
            static constexpr auto LOG_SKIP_EXPORT = "Skipping export using {}";
            LOG_DEBUG(LOG_SKIP_EXPORT, typeid(*exporter).name());
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
                    static constexpr auto LOG_MATCH_FOUND = "Matching widget has been found with class \"{}\" and name \"{}\"";
                    LOG_DEBUG(LOG_MATCH_FOUND, widget->metaObject()->className(), widget->objectName().toStdString());
                    foundWidgets[className][objectName].push_front(widget);
                }
            }
            exporter->exportUI(foundWidgets[className][objectName]);
        }
    }
    ExtensionsManager::clearMessage();
}