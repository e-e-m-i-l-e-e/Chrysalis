#include "UIExporterToolSettings.h"

void UIExporterToolSettings::save() {
}

void UIExporterToolSettings::reset() {
}

void UIExporterToolSettings::addOptions(const std::shared_ptr<BaseUIExporterOptions> &options) {
    options_.push_front(options);
}

std::forward_list<std::shared_ptr<BaseUIExporterOptions>>::const_iterator UIExporterToolSettings::begin() const {
    return options_.begin();
}

std::forward_list<std::shared_ptr<BaseUIExporterOptions>>::const_iterator UIExporterToolSettings::end() const {
    return options_.end();
}
