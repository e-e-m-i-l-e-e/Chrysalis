#include "CustomWidgetsPlugin.h"

#include "AccordionPlugin.h"
#include "AccordionTitleContainerPlugin.h"

QList<QDesignerCustomWidgetInterface *> CustomWidgetInterface::customWidgets() const {
    return {
        new AccordionPlugin(),
        new AccordionTitleContainerPlugin()
    };
}
