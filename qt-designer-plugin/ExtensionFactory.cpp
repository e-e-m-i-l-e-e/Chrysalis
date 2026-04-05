#include "ExtensionFactory.h"

#include "AccordionContainerExtension.h"

ExtensionFactory::ExtensionFactory(QExtensionManager *parent): QExtensionFactory(parent) {}

QObject * ExtensionFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const {
    if (iid != Q_TYPEID(QDesignerContainerExtension))
        return nullptr;

    if (auto *accordion = qobject_cast<UI::Accordion*>(object))
        return new AccordionContainerExtension(accordion, parent);
    return nullptr;
}
