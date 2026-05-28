#ifndef CLOEXTENSIONS_CUSTOMWIDGETINTERFACE_H
#define CLOEXTENSIONS_CUSTOMWIDGETINTERFACE_H

#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>

#include "ExtensionFactory.h"

class DesignerPlugin: public QObject, public QDesignerCustomWidgetCollectionInterface {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    QList<QDesignerCustomWidgetInterface*> customWidgets() const override; // NOLINT(*-use-nodiscard)
};

#endif //CLOEXTENSIONS_CUSTOMWIDGETINTERFACE_H