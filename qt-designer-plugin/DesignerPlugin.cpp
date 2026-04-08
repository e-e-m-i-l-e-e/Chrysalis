#include "DesignerPlugin.h"

#include "AccordionContainerPlugin.h"
#include "AccordionTitleContainerPlugin.h"
#include "TableContentContainerPlugin.h"
#include "TableInputAccordionPlugin.h"

DesignerPlugin::DesignerPlugin() {
    accordionTitleContainerPlugin = new AccordionTitleContainerPlugin();
}

QList<QDesignerCustomWidgetInterface*> DesignerPlugin::customWidgets() const {
    return {
        accordionTitleContainerPlugin,
        new AccordionContainerPlugin(),
        new TableContentContainerPlugin(),
        new TableInputAccordionPlugin()
    };
}
