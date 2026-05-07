#include "UIExporterToolSettings.h"

void UIExporterToolSettings::read() {
    settings_->beginGroup(typeid(*this).name());
    for (const auto& options : options_) {
        settings_->beginGroup(typeid(*options).name());
        options->read(settings_);
        settings_->endGroup();
    }
    settings_->endGroup();
}

void UIExporterToolSettings::write() {
    settings_->beginGroup(typeid(*this).name());
    for (const auto& options : options_) {
        settings_->beginGroup(typeid(*options).name());
        options->write(settings_);
        settings_->endGroup();
    }
    settings_->endGroup();
}

void UIExporterToolSettings::addOptions(BaseUIExporterOptions* options) {
    options_.push_back(options);
}

std::list<BaseUIExporterOptions*>::const_iterator UIExporterToolSettings::begin() const {
    return options_.begin();
}

std::list<BaseUIExporterOptions*>::const_iterator UIExporterToolSettings::end() const {
    return options_.end();
}
