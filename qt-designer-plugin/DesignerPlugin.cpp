#include "DesignerPlugin.h"

#include "AccordionPlugin.h"
#include "AccordionTitleContainerPlugin.h"

QList<QDesignerCustomWidgetInterface*> DesignerPlugin::customWidgets() const {
    accordionTitleContainerPlugin = new AccordionTitleContainerPlugin();
    return {
        new AccordionPlugin(),
        accordionTitleContainerPlugin
    };
}
