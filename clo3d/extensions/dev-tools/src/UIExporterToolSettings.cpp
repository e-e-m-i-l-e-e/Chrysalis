#include "UIExporterToolSettings.h"

void UIExporterToolSettings::addOptions(BaseUIExporterOptions* options) {
    options_.push_back(options);
}

std::list<BaseUIExporterOptions*>::const_iterator UIExporterToolSettings::begin() const {
    return options_.begin();
}

std::list<BaseUIExporterOptions*>::const_iterator UIExporterToolSettings::end() const {
    return options_.end();
}
