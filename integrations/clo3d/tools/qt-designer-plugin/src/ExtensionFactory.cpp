#include "ExtensionFactory.h"

#include "BaseDialogContainer.h"
#include "BaseDialogContainerExtension.h"
#include "BaseUIExporterSettingsBlockContainerWidget.h"
#include "BaseUIExporterSettingsBlockContainerWidgetExtension.h"
#include "TableInputAccordionExtension.h"
#include "SettingsBlockContainerWidget.h"
#include "SettingsBlockContainerWidgetExtension.h"

using namespace CLO3D::UI;

ExtensionFactory::ExtensionFactory(QExtensionManager* parent): QExtensionFactory(parent) {}

QObject* ExtensionFactory::createExtension(QObject* object, const QString& iid, QObject* parent) const {
    if (iid == Q_TYPEID(QDesignerContainerExtension)) {
        if (auto* widget = qobject_cast<TableInputAccordion*>(object)) {
            return new TableInputAccordionExtension(widget, parent);
        }
        if (auto* widget = qobject_cast<SettingsBlockContainerWidget*>(object)) {
            return new SettingsBlockContainerWidgetExtension(widget, parent);
        }
        if (auto* widget = qobject_cast<BaseUIExporterSettingsBlockContainerWidget*>(object)) {
            return new BaseUIExporterSettingsBlockContainerWidgetExtension(widget, parent);
        }
        if (auto* dialog = qobject_cast<BaseDialogContainer*>(object)) {
            return new BaseDialogContainerExtension(dialog, parent);
        }
    }
    return nullptr;
}
