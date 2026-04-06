#include "ExtensionFactory.h"

#include "AccordionContainerExtension.h"
#include "AccordionTitleContainerExtension.h"

ExtensionFactory::ExtensionFactory(QExtensionManager* parent): QExtensionFactory(parent) {}

QObject* ExtensionFactory::createExtension(QObject* object, const QString& iid, QObject* parent) const {
    if (iid == Q_TYPEID(QDesignerContainerExtension)) {
        if (auto *accordion = qobject_cast<UI::Accordion*>(object)) {
            return new AccordionContainerExtension(accordion, parent);
        }
        if (auto* accordionTitle = qobject_cast<UI::AccordionTitleContainer*>(object)) {
            return new AccordionTitleContainerExtension(accordionTitle, parent);
        }
    }
    return nullptr;
}
