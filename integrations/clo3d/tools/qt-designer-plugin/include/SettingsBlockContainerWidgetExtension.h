#ifndef CHRYSALIS_SETTINGSBLOCKCONTAINERWIDGETEXTENSION_H
#define CHRYSALIS_SETTINGSBLOCKCONTAINERWIDGETEXTENSION_H

#include "ContainerExtension.h"
#include "SettingsBlockContainerWidget.h"

class SettingsBlockContainerWidgetExtension: public ContainerExtension {
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)
public:
    SettingsBlockContainerWidgetExtension(UI::SettingsBlockContainerWidget *container, QObject *parent)
    : ContainerExtension(container, parent) {}
};

#endif //CHRYSALIS_SETTINGSBLOCKCONTAINERWIDGETEXTENSION_H