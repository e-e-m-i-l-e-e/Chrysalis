#ifndef CHRYSALIS_BASEDIALOGCONTAINERPLUGIN_H
#define CHRYSALIS_BASEDIALOGCONTAINERPLUGIN_H

#include "ContainerPlugin.h"

namespace CLO3D::UI {
    class BaseDialogContainerPlugin: public ContainerPlugin {
        Q_OBJECT
        Q_INTERFACES(QDesignerCustomWidgetInterface)
    public:
        QWidget* createWidget(QWidget* parent) override;
    protected:
        [[nodiscard]] QStringList domXmlContent() const override;
    };
}

#endif //CHRYSALIS_BASEDIALOGCONTAINERPLUGIN_H