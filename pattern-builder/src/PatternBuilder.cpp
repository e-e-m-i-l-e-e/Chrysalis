#include "PatternBuilder.h"

#define LOGGER_NAME "Pattern Builder"

#include <CLOAPIInterface.h>
#include <QLayout>
#include <QMainWindow>

#include "Logger.h"
#include "MVDockingButton.h"
#include "PatternBuilderDockWidget.h"
#include "MVDockWidgetTitleBar.h"
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
    } else if (widget->objectName() == "DummyDockingWindow") {
        const auto mainWindow = qobject_cast<QMainWindow*>(widget);
        const auto patternBuilderDockWidget = new PatternBuilderDockWidget(widget);
        mainWindow->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, patternBuilderDockWidget);
        patternBuilderDockWidget->setTitleBarWidget(new MVDockWidgetTitleBar());
    }
}