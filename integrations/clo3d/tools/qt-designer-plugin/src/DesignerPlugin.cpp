#include "DesignerPlugin.h"

#include "NamedWidgetPlugin.h"
#include "BaseDialogContainerPlugin.h"
#include "TableInputAccordionPlugin.h"
#include "ListNavigationWidgetPlugin.h"
#include "SettingsBlockContainerWidget.h"
#include "SettingsBlockContainerWidgetPlugin.h"
#include "BaseUIExporterSettingsBlockContainerWidgetPlugin.h"

QList<QDesignerCustomWidgetInterface*> DesignerPlugin::customWidgets() const {
    return {
        new NamedWidgetPlugin(),
        new BaseDialogContainerPlugin(),
        new TableInputAccordionPlugin(),
        new ListNavigationWidgetPlugin(),
        new SettingsBlockContainerWidgetPlugin(),
        new BaseUIExporterSettingsBlockContainerWidgetPlugin()
    };
}
