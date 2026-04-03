#include "PatternBuilderDockWidget.h"

#include <CLOAPIInterface.h>

#include "ui_PatternBuilderDockWidget.h"
#include "clo-ui-common/TabBar.h"


PatternBuilderDockWidget::PatternBuilderDockWidget(QWidget *parent) : MVDockWidget(parent),
                                                                      ui(new Ui::PatternBuilderDockWidget) {
    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);
    ui->tabWidget->tabBar()->setExpanding(true);
    ui->tabWidget->tabBar()->setDocumentMode(true);
    // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // ui->scrollArea->viewport()->setAutoFillBackground(false);
    // ui->scrollArea->viewport()->setStyleSheet("background: transparent;");
}

PatternBuilderDockWidget::~PatternBuilderDockWidget() {
    delete ui;
}