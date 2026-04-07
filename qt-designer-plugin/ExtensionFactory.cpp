#include "ExtensionFactory.h"

#include "AccordionContainerExtension.h"
#include "AccordionTitleContainerExtension.h"
#include "TableContentContainer.h"
#include "TableContentContainerExtension.h"

ExtensionFactory::ExtensionFactory(QExtensionManager* parent, int count): QExtensionFactory(parent), count_(count) {}

QObject* ExtensionFactory::createExtension(QObject* object, const QString& iid, QObject* parent) const {
    if (iid == Q_TYPEID(QDesignerContainerExtension)) {
        if (auto *accordion = qobject_cast<UI::AccordionContainer*>(object)) {
            return new AccordionContainerExtension(accordion, parent, count_);
        }
        if (auto* accordionTitle = qobject_cast<UI::AccordionTitleContainer*>(object)) {
            return new AccordionTitleContainerExtension(accordionTitle, parent, {2});
        }
        if (auto* tableContent = qobject_cast<UI::TableContentContainer*>(object)) {
            return new TableContentContainerExtension(tableContent, parent, {0, 2});
        }
    }
    return nullptr;
}
