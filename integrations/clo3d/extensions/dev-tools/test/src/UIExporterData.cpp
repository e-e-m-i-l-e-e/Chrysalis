#include "data/UIExporterData.h"

UIExporterData::UIExporterData(std::function<std::forward_list<QWidget*>()>&& factory): factory_(factory) {}

std::forward_list<QWidget*> UIExporterData::widgets() const {
    return factory_();
}
