#include "DesignerPlugin.h"

#include "AccordionContainerPlugin.h"
#include "AccordionTitleContainerPlugin.h"

QList<QDesignerCustomWidgetInterface*> DesignerPlugin::customWidgets() const {
    accordionTitleContainerPlugin = new AccordionTitleContainerPlugin();
    return {
        new AccordionContainerPlugin(),
        accordionTitleContainerPlugin
    };
}
