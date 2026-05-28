#ifndef CHRYSALIS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGETEXTENSION_H
#define CHRYSALIS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGETEXTENSION_H

#include "ContainerExtension.h"
#include "BaseUIExporterSettingsBlockContainerWidget.h"

class BaseUIExporterSettingsBlockContainerWidgetExtension: public ContainerExtension {
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)
public:
    BaseUIExporterSettingsBlockContainerWidgetExtension(UI::BaseUIExporterSettingsBlockContainerWidget* container, QObject *parent)
    : ContainerExtension(container, parent) {}
};


#endif //CHRYSALIS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGETEXTENSION_H