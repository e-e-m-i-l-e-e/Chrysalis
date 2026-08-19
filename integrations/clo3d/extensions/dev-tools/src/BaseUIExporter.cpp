#include "BaseUIExporter.h"

#include <memory>
#include <forward_list>

#include <QWidget>
#include <QApplication>

#include "BaseTask.h"
#include "TaskGroup.h"

#include "Logging.h"
#define LOGGER_NAME "UI Exporter"

using namespace CLO3D;

void BaseUIExporter::exportUI(QWidget* widget) {
    exportUI(std::forward_list{widget});
}
