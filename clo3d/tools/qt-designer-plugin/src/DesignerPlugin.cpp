#include "DesignerPlugin.h"

#include "TableInputAccordionPlugin.h"

QList<QDesignerCustomWidgetInterface*> DesignerPlugin::customWidgets() const {
    return {
        new TableInputAccordionPlugin()
    };
}
