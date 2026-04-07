#include "DesignerPlugin.h"

#include "AccordionContainerPlugin.h"
#include "AccordionTitleContainerPlugin.h"
#include "TableContentContainerPlugin.h"

QList<QDesignerCustomWidgetInterface*> DesignerPlugin::customWidgets() const {
    accordionTitleContainerPlugin = new AccordionTitleContainerPlugin();
    return {
        new AccordionContainerPlugin(),
        accordionTitleContainerPlugin,
        new TableContentContainerPlugin()
    };
}
