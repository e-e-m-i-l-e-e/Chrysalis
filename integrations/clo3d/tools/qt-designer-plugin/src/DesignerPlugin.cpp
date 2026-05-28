#include "DesignerPlugin.h"

#include "BaseUIExporterSettingsBlockContainerWidgetPlugin.h"
#include "ListNavigationWidgetPlugin.h"
#include "NamedWidgetPlugin.h"
#include "SettingsBlockContainerWidget.h"
#include "SettingsBlockContainerWidgetPlugin.h"
#include "TableInputAccordionPlugin.h"

QList<QDesignerCustomWidgetInterface*> DesignerPlugin::customWidgets() const {
    return {
        new NamedWidgetPlugin(),
        new TableInputAccordionPlugin(),
        new ListNavigationWidgetPlugin(),
        new SettingsBlockContainerWidgetPlugin(),
        new BaseUIExporterSettingsBlockContainerWidgetPlugin()
    };
}
