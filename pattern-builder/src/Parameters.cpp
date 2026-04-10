#include "Parameters.h"

#include <CLOAPIInterface.h>

#include "Logger.h"
#include "ui_Parameters.h"

#define LOGGER_NAME "Parameters"

namespace UI::PatternBuilder {
    Parameters::Parameters(QWidget *parent) : QWidget(parent), ui(new Ui::Parameters) {
        ui->setupUi(this);
        UTILITY_API->UpdateCloStyleForPlugIn(this);
        ui->avatarMeasuresAccordion->install({ui->customTools_2, ui->beforeTable_2, ui->afterTable_2});

        for (const auto& avatar: EXPORT_API->GetAvatarNameList()) {
            LOG_INFO("Avatar name: {}", avatar);
        }
    }

    Parameters::~Parameters() {
        delete ui;
    }
} // UI::PatternBuilder