#ifndef FASHIONDESIGNAPPS_SETTINGSBLOCKCONTAINERPLUGIN_H
#define FASHIONDESIGNAPPS_SETTINGSBLOCKCONTAINERPLUGIN_H

#include "ContainerPlugin.h"

class SettingsBlockContainerWidgetPlugin: public ContainerPlugin {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    QWidget * createWidget(QWidget *parent) override;
protected:
    [[nodiscard]] QStringList domXmlContent() const override;
};

#endif //FASHIONDESIGNAPPS_SETTINGSBLOCKCONTAINERPLUGIN_H