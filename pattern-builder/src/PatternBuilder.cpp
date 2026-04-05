#include "PatternBuilder.h"

#define LOGGER_NAME "Pattern Builder"

#include <CLOAPIInterface.h>
#include <QLayout>
#include <QMainWindow>
#include <QMainWindow>

#include "Logger.h"
#include "MVDockingButton.h"
#include "PatternBuilderDockWidget.h"
#include "MVDockWidgetTitleBar.h"
#include "Accordion.h"
#include "clo-ui-common/IconButton.h"

void PatternBuilder::configureStatusBar(QWidget *parent) {
    for (const auto childIcon: parent->findChildren<QToolButton*>()) {
        if (childIcon->toolTip() == "3D / 2D Window") {

            // TODO:
            //      - change icon on hover
            //      - configure clicks

            const auto patternBuilderIcon = new QToolButton(parent);

            patternBuilderIcon->setIcon(QIcon(":/patternBuilder.png"));

            patternBuilderIcon->setIconSize(childIcon->iconSize());
            patternBuilderIcon->setFixedSize(childIcon->size());
            patternBuilderIcon->setStyleSheet(childIcon->styleSheet());

            patternBuilderIcon->setToolTip("Pattern Builder");

            patternBuilderIcon->move(childIcon->pos().x() - childIcon->width(), childIcon->pos().y());
            patternBuilderIcon->show();
            return;
        }
    }
    LOG_CRITICAL("\"Pattern Builder\" cannot be configured. \"3D / 2D Window\" wasn't found in status bar.");
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

        const auto w = new UI::Accordion(widget);
        w->show();
    }
}