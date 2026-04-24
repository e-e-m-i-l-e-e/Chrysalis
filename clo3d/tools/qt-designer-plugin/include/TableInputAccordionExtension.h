#ifndef CLOEXTENSIONS_TABLEINPUTACCORDIONEXTENSION_H
#define CLOEXTENSIONS_TABLEINPUTACCORDIONEXTENSION_H

#include "ContainerExtension.h"
#include "TableInputAccordion.h"

class TableInputAccordionExtension: public ContainerExtension {
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)
public:
    explicit TableInputAccordionExtension(UI::TableInputAccordion* container, QObject* parent)
    : ContainerExtension(container, parent) {}
};

#endif //CLOEXTENSIONS_TABLEINPUTACCORDIONEXTENSION_H