#ifndef CHRYSALIS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGETPLUGIN_H
#define CHRYSALIS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGETPLUGIN_H

#include "ContainerPlugin.h"

class BaseUIExporterSettingsBlockContainerWidgetPlugin: public ContainerPlugin {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    QWidget* createWidget(QWidget *parent) override;
protected:
    [[nodiscard]] QStringList domXmlContent() const override;
};

#endif //CHRYSALIS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGETPLUGIN_H