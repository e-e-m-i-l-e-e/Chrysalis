#ifndef CHRYSALIS_CUSTOMWIDGETINTERFACE_H
#define CHRYSALIS_CUSTOMWIDGETINTERFACE_H

#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>

#include "ExtensionFactory.h"

namespace CLO3D::UI {
    class DesignerPlugin: public QObject, public QDesignerCustomWidgetCollectionInterface {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
        Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
    public:
        QList<QDesignerCustomWidgetInterface*> customWidgets() const override; // NOLINT(*-use-nodiscard)
    };
}

#endif //CHRYSALIS_CUSTOMWIDGETINTERFACE_H