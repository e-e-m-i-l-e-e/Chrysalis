#ifndef CHRYSALIS_SETTINGSBLOCKCONTAINERPLUGIN_H
#define CHRYSALIS_SETTINGSBLOCKCONTAINERPLUGIN_H

#include "ContainerPlugin.h"

class SettingsBlockContainerWidgetPlugin: public ContainerPlugin {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    QWidget * createWidget(QWidget *parent) override;
protected:
    [[nodiscard]] QStringList domXmlContent() const override;
};

#endif //CHRYSALIS_SETTINGSBLOCKCONTAINERPLUGIN_H