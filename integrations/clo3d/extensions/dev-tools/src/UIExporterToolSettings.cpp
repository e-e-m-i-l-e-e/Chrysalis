#include "UIExporterToolSettings.h"

using namespace CLO3D;

void UIExporterToolSettings::read() {
    for (const auto& options : options_) {
        settings_->beginGroup(typeid(*options).name() + 6);
        options->read(settings_);
        settings_->endGroup();
    }
}

void UIExporterToolSettings::write() {
    for (const auto& options : options_) {
        settings_->beginGroup(typeid(*options).name() + 6);
        options->write(settings_);
        settings_->endGroup();
    }
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
