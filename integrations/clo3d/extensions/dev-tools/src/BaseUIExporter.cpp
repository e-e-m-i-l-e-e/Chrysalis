#include "BaseUIExporter.h"

#include <forward_list>

#include <QWidget>
#include <QApplication>

#include "Logging.h"
#define LOGGER_NAME "UI Exporter"

void BaseUIExporter::exportUI() {
    LOG_INFO("No filters applied. Top-level widgets will be exported by {}.", typeid(*this).name() + 6);
    std::forward_list<QWidget*> widgets;
    for (const auto widget: QApplication::topLevelWidgets()) {
        if (!widget->parent()) {
            LOG_INFO("Widget with class name \"{}\" and object name \"{}\" will be exported.", widget->metaObject()->className(), widget->objectName().toStdString());
            widgets.push_front(widget);
        }
    }
    exportUI(widgets);
}

void BaseUIExporter::exportUI(QWidget* widget) {
    exportUI(std::forward_list{widget});
}
