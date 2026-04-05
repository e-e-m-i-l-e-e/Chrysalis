#include "Accordion.h"
#include "ui_Accordion.h"

namespace UI {
    Accordion::Accordion(QWidget *parent) : QWidget(parent), ui(new Ui::Accordion) {
        ui->setupUi(this);
    }

    Accordion::~Accordion() {
        delete ui;
    }

    QWidget *Accordion::titleWidget() const {
        return ui->titleWidget;
    }

    QWidget *Accordion::contentWidget() const {
        return ui->contentWidget;
    }
} // UI