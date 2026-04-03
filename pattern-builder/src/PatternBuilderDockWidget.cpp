#include "PatternBuilderDockWidget.h"

#include <CLOAPIInterface.h>

#include "ui_PatternBuilderDockWidget.h"
#include "clo-ui-common/TabBar.h"


PatternBuilderDockWidget::PatternBuilderDockWidget(QWidget *parent) : MVDockWidget(parent),
                                                                      ui(new Ui::PatternBuilderDockWidget) {
    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

PatternBuilderDockWidget::~PatternBuilderDockWidget() {
    delete ui;
}