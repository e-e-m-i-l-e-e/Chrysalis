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

        connect(ui->avatarMeasuresAccordion->getAccordionTitle(), &ClickableWidget::clicked, this, [] {
            for (const auto &avatar: EXPORT_API->GetAvatarNameList()) {
                LOG_INFO("Avatar name: {}", avatar);
            }
            for (int i = 0; i < EXPORT_API->GetAvatarCount(); i++) {
                for (auto property: UTILITY_API->GetAvatarProperties(i)) {
                    LOG_INFO("Avatar property. Name: {} value: {}", property.first, property.second);
                }
            }
        });
    }

    Parameters::~Parameters() {
        delete ui;
    }
} // UI::PatternBuilder