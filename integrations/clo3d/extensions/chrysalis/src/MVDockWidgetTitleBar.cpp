#include "MVDockWidgetTitleBar.h"
#include "ui_MVDockWidgetTitleBar.h"

using namespace CLO3D::UI;

MVDockWidgetTitleBar::MVDockWidgetTitleBar(QWidget *parent) : MVDockWidgetTitleBarBase(parent),
                                                              ui(new Ui::MVDockWidgetTitleBar) {
    ui->setupUi(this);
}

MVDockWidgetTitleBar::~MVDockWidgetTitleBar() {
    delete ui;
}