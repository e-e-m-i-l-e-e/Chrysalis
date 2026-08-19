#ifndef CHRYSALIS_TABLEINPUTACCORDIONEXTENSION_H
#define CHRYSALIS_TABLEINPUTACCORDIONEXTENSION_H

#include "ContainerExtension.h"
#include "TableInputAccordion.h"

namespace CLO3D::UI {
    class TableInputAccordionExtension: public ContainerExtension {
        Q_OBJECT
        Q_INTERFACES(QDesignerContainerExtension)
    public:
        explicit TableInputAccordionExtension(UI::TableInputAccordion* container, QObject* parent)
        : ContainerExtension(container, parent) {}
    };
}

#endif //CHRYSALIS_TABLEINPUTACCORDIONEXTENSION_H