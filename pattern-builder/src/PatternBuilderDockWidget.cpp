#include "PatternBuilderDockWidget.h"
#include "ui_PatternBuilderDockWidget.h"


PatternBuilderDockWidget::PatternBuilderDockWidget(QWidget *parent) : MVDockWidget(parent),
                                                                      ui(new Ui::PatternBuilderDockWidget) {
    ui->setupUi(this);
}

PatternBuilderDockWidget::~PatternBuilderDockWidget() {
    delete ui;
}