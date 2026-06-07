#include "ChrysalisExtension.h"

#include "Logging.h"
#define LOGGER_NAME "Chrysalis Extension"

#include <QLayout>
#include <QFileDialog>
#include <QMainWindow>
#include <QToolButton>

#include "Project.h"
#include "MVDockingButton.h"
#include "MVDockWidgetTitleBar.h"
#include "PatternBuilderDockWidget.h"
#include "PatternImportDialog.h"

using namespace Chrysalis;

void ChrysalisExtension::configureMenu(QMenu* extensionMenu) {
    const auto menu = new QMenu("Chrysalis", extensionMenu);
    extensionMenu->addMenu(menu);

    const auto fileDialog = new QFileDialog(menu);
    fileDialog->setNameFilter(Project::PROJECT_NAME_FILTER);
    fileDialog->setDefaultSuffix(Project::PROJECT_FILE_SUFFIX);

    const auto importPatternAction = new QAction("Import", menu);
    QObject::connect(importPatternAction, &QAction::triggered, fileDialog, [fileDialog]{
        fileDialog->exec();
    });
    QObject::connect(fileDialog, &QFileDialog::accepted, importPatternAction, [fileDialog] {
        const auto& filePath = fileDialog->selectedFiles().first().toStdString();
        LOG_INFO("Importing project: {}", filePath);

        const auto project = Project::read(filePath);
        const auto importer = new PatternImporter(project);
        const auto parametersModel = new UI::BaseModel(project->getParameters());
        const auto parametersDelegate = new UI::BaseDelegate<UI::ParameterWidget, Parameter>(parametersModel);
        (new UI::PatternImportDialog(importer, parametersModel, parametersDelegate))->exec();
    });
    menu->addAction(importPatternAction);
}

void ChrysalisExtension::configureStatusBar(QWidget *parent) {
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

            LOG_INFO("Position: {}, {}", childIcon->pos().x() - childIcon->width(), childIcon->pos().y());

            patternBuilderIcon->move(childIcon->pos().x() - childIcon->width(), childIcon->pos().y());
            patternBuilderIcon->show();
            return;
        }
    }
    LOG_CRITICAL("\"Pattern Builder\" cannot be configured. \"3D / 2D Window\" wasn't found in status bar.");
}

void ChrysalisExtension::configure(QWidget *widget) {
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

        patternBuilderDockWidget->setStyleSheet("background-color: rgb(37, 37, 40);");
    }
}