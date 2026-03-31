#include "PatternBuilder.h"

#define LOGGER_NAME "Pattern Builder"

#include <CLOAPIInterface.h>
#include <QLayout>
#include <QMainWindow>

#include "Logger.h"
#include "MVDockingButton.h"
#include "PatternBuilderDockWidget.h"
#include "clo-ui-common/IconButton.h"

void PatternBuilder::configureStatusBar(QWidget *parent) {
    const auto patternBuilderIcon = new CloUICommon::IconButton(parent);
    // patternBuilderIcon->setGeometry(parent->width() * 2 / 3, 2, 500, 20);
    patternBuilderIcon->show();
}

void PatternBuilder::configure(QWidget *widget) {
    if (widget->objectName() == "dockingBarContents" && widget->parent()->findChild<QAction*>()->iconText() == "Right Docking Bar") {
        LOG_INFO("Configuring right docking bar.");
        const auto patternBuilderDockItem = new MVDockingButton(widget);
        qobject_cast<QVBoxLayout*>(widget->layout())->insertWidget(8, patternBuilderDockItem);
        patternBuilderDockItem->show();

        new PatternBuilderDockWidget(widget);
    } else if (widget->objectName() == "DummyDockingWindow") {
        const auto mainWindow = qobject_cast<QMainWindow*>(widget);
        for (auto docks: mainWindow->findChildren<QDockWidget*>()) {
            LOG_INFO("Docking widget: {}", docks->objectName().toStdString());
        }
        mainWindow->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, new PatternBuilderDockWidget(widget));
    }
}