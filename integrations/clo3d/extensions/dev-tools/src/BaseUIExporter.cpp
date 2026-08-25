#include "BaseUIExporter.h"

#include <forward_list>

#include <QWidget>
#include <QApplication>


#define LOGGER_NAME "UI Exporter"

using namespace CLO3D;

void BaseUIExporter::exportUI(QWidget* widget) {
    exportUI(std::forward_list{widget});
}
