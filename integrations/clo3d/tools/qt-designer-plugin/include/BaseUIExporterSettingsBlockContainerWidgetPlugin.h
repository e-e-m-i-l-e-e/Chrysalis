#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGETPLUGIN_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGETPLUGIN_H

#include "ContainerPlugin.h"

class BaseUIExporterSettingsBlockContainerWidgetPlugin: public ContainerPlugin {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    QWidget* createWidget(QWidget *parent) override;
protected:
    [[nodiscard]] QStringList domXmlContent() const override;
};

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGETPLUGIN_H