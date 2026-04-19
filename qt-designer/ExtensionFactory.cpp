#include "ExtensionFactory.h"

#include "TableInputAccordion.h"
#include "TableInputAccordionExtension.h"

ExtensionFactory::ExtensionFactory(QExtensionManager* parent, const int count): QExtensionFactory(parent), count_(count) {}

QObject* ExtensionFactory::createExtension(QObject* object, const QString& iid, QObject* parent) const {
    if (iid == Q_TYPEID(QDesignerContainerExtension)) {
        if (auto* tableInputAccordion = qobject_cast<UI::TableInputAccordion*>(object)) {
            return new TableInputAccordionExtension(tableInputAccordion, parent, count_);
        }
    }
    return nullptr;
}
