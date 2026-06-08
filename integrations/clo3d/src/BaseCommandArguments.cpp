#include "BaseCommandArguments.h"

BaseCommandArguments::BaseCommandArguments(QSettings* settings): settings_(settings) {}

void BaseCommandArguments::readSettings() {
    settings_->beginGroup("Commands");
    settings_->beginGroup(getName());
    read();
    settings_->endGroup();
    settings_->endGroup();
}

void BaseCommandArguments::writeSettings() {
    settings_->beginGroup("Commands");
    settings_->beginGroup(getName());
    write();
    settings_->endGroup();
    settings_->endGroup();
}
