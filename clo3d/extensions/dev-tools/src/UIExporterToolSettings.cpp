#include "UIExporterToolSettings.h"

void UIExporterToolSettings::readSettings() {
    const auto settings = editSettings(typeid(*this).name());
    for (const auto& options : options_) {
        options->read(editSettings(typeid(*options).name()));
    }
}

void UIExporterToolSettings::writeSettings() {
    const auto settings = editSettings(typeid(*this).name());
    for (const auto& options : options_) {
        options->write(editSettings(typeid(*options).name()));
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
