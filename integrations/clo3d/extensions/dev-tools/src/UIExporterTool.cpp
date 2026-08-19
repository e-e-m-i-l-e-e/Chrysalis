#include "UIExporterTool.h"

#include <unordered_map>

#include <QApplication>

#include "XmlUIExporter.h"
#include "JsonUIExporter.h"
#include "ExtensionsManager.h"
#include "UIExporterToolSettings.h"
#include "UIExporterToolSettingsWidget.h"

#include "Logging.h"
#include "TaskGroup.h"
#define LOGGER_NAME "UI Exporter"

using namespace CLO3D;

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
        LOG_DEBUG(
            "Exporting widget at cursor position. Class name: {}. Object name: {}.",
            widgetAtMousePosition->metaObject()->className(),
            widgetAtMousePosition->objectName().toStdString()
        );
    }
    for (const auto exporter: exporters_) {
        const auto options = exporter->getOptions();
        if (!options->isEnabled()) {
            LOG_DEBUG("Skipping export using {}", typeid(*exporter).name());
            continue;
        }
        if (!options->getRootFolder().exists()) {
            if (options->getRootFolder().mkpath(".")) {
                LOG_INFO("\"{}\" directory was created.", options->getRootFolder().path().toStdString());
            } else {
                LOG_ERROR("Failed to create directory: {}.", options->getRootFolder().path().toStdString());
                continue;
            }
        }
        if (widgetAtMousePosition) {
            exporter->exportUI(widgetAtMousePosition);
        } else if (options->getClassName().isEmpty() && options->getObjectName().isEmpty()) {
            LOG_INFO("No filters applied. Top-level widgets will be exported by {}.", typeid(*this).name() + 6);
            std::forward_list<QWidget*> widgets;
            for (const auto widget: QApplication::topLevelWidgets()) {
                if (!widget->parent()) {
                    LOG_INFO(
                        "Widget with class name \"{}\" and object name \"{}\" will be exported.",
                        widget->metaObject()->className(),
                        widget->objectName().toStdString()
                    );
                    widgets.push_front(widget);
                }
            }
            exporter->exportUI(std::move(widgets));
        } else {
            std::forward_list<QWidget*> foundWidgets; // <className, <objectName, widgets>>
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
                    foundWidgets.push_front(widget);
                }
            }
            exporter->exportUI(std::move(foundWidgets));
        }
    }
}