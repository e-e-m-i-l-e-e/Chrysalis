#include "PatternBuilderDockWidget.h"

#include <CLOAPIInterface.h>

#include "Logger.h"
#include "ui_PatternBuilderDockWidget.h"

#include <QTabBar>

#define LOGGER_NAME "PatternBuilderDockWidget"


PatternBuilderDockWidget::PatternBuilderDockWidget(QWidget *parent) : QDockWidget(parent),
                                                                      ui(new Ui::PatternBuilderDockWidget) {
    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);
    ui->tabWidget->tabBar()->setExpanding(true);
    ui->tabWidget->tabBar()->setDocumentMode(true);
    // connect(ui->tabWidget, &QTabWidget::tabBarClicked, [this](int index) {
    //     // UTILITY_API->CreateProgressBar();
    //     IMPORT_API->ImportAvatar("C:/Users/Public/Documents/CLO/CLO Assets/Avatar/Female/FV2.1_Mia.avt", {});
    // });
    // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // ui->scrollArea->viewport()->setAutoFillBackground(false);
    // ui->scrollArea->viewport()->setStyleSheet("background: transparent;");
}

PatternBuilderDockWidget::~PatternBuilderDockWidget() {
    delete ui;
}