#include "BaseCommandArgumentsWidget.h"

#include "CLOAPIInterface.h"

using namespace CLO3D::UI;

BaseCommandArgumentsWidget::BaseCommandArgumentsWidget(BaseCommandArguments* arguments): arguments_(arguments) {
    UTILITY_API->UpdateCloStyleForPlugIn(this);
}

void BaseCommandArgumentsWidget::load() {
    arguments_->readSettings();
}

void BaseCommandArgumentsWidget::save() const {
    arguments_->writeSettings();
}
