#include "ExtensionFactory.h"

#include "BaseUIExporterSettingsBlockContainerWidget.h"
#include "BaseUIExporterSettingsBlockContainerWidgetExtension.h"
#include "TableInputAccordionExtension.h"
#include "ListNavigationWidgetExtension.h"
#include "SettingsBlockContainerWidget.h"
#include "SettingsBlockContainerWidgetExtension.h"

ExtensionFactory::ExtensionFactory(QExtensionManager* parent): QExtensionFactory(parent) {}

QObject* ExtensionFactory::createExtension(QObject* object, const QString& iid, QObject* parent) const {
    if (iid == Q_TYPEID(QDesignerContainerExtension)) {
        if (auto* widget = qobject_cast<UI::TableInputAccordion*>(object)) {
            return new TableInputAccordionExtension(widget, parent);
        }
        if (auto* widget = qobject_cast<UI::ListNavigationWidget*>(object)) {
            return new ListNavigationWidgetExtension(widget, parent);
        }
        if (auto* widget = qobject_cast<UI::SettingsBlockContainerWidget*>(object)) {
            return new SettingsBlockContainerWidgetExtension(widget, parent);
        }
        if (auto* widget = qobject_cast<UI::BaseUIExporterSettingsBlockContainerWidget*>(object)) {
            return new BaseUIExporterSettingsBlockContainerWidgetExtension(widget, parent);
        }
    }
    return nullptr;
}
