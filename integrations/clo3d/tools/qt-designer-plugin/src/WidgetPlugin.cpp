#include "WidgetPlugin.h"

#include "Logging.h"
#define LOGGER_NAME "Designer Plugin"

using namespace CLO3D::UI;

QString WidgetPlugin::name() const {
    return QString(this->metaObject()->className()).remove("Plugin");
}

QString WidgetPlugin::group() const {
    return "Other";
}

QString WidgetPlugin::toolTip() const {
    return {};
}

QString WidgetPlugin::whatsThis() const {
    return {};
}

QString WidgetPlugin::includeFile() const {
    return QString(this->metaObject()->className()).remove("Plugin").append(".h");
}

QIcon WidgetPlugin::icon() const {
    return {};
}

bool WidgetPlugin::isContainer() const {
    return false;
}

void WidgetPlugin::initialize(QDesignerFormEditorInterface *core) {
    LOG_INFO("Initializing custom \"{}\" widget.", this->metaObject()->className());
}
