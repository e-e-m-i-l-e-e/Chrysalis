#include "Accordion.h"
#include "ui_Accordion.h"

namespace UI {
    Accordion::Accordion(QWidget *parent) : QWidget(parent), ui(new Ui::Accordion) {
        ui->setupUi(this);
    }

    Accordion::~Accordion() {
        delete ui;
    }

    QString Accordion::getTitle() const {
        return ui->title->text();
    }

    void Accordion::setTitle(const QString& title) const {
        ui->title->setText(title);
    }
} // UI