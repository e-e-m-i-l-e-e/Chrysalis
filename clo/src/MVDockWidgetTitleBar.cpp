#include "MVDockWidgetTitleBar.h"
#include "ui_MVDockWidgetTitleBar.h"


MVDockWidgetTitleBar::MVDockWidgetTitleBar(QWidget *parent) : MVDockWidgetTitleBarBase(parent),
                                                              ui(new Ui::MVDockWidgetTitleBar) {
    ui->setupUi(this);
}

MVDockWidgetTitleBar::~MVDockWidgetTitleBar() {
    delete ui;
}