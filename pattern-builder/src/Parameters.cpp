//
// Created by emily on 08/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Parameters.h" resolved

#include "Parameters.h"

#include <CLOAPIInterface.h>

#include "ui_Parameters.h"

namespace UI::PatternBuilder {
    Parameters::Parameters(QWidget *parent) : QWidget(parent), ui(new Ui::Parameters) {
        ui->setupUi(this);
        UTILITY_API->UpdateCloStyleForPlugIn(this);
        ui->avatarMeasuresAccordion->install({ui->customTools_2, ui->beforeTable_2, ui->afterTable_2});
        // UTILITY_API->UpdateCloStyleForPlugIn(ui->avatarMeasuresAccordion);
    }

    Parameters::~Parameters() {
        delete ui;
    }
} // UI::PatternBuilder