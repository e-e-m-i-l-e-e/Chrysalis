#ifndef CLOEXTENSIONS_ACCORDIONTITLECONTAINEREXTENSION_H
#define CLOEXTENSIONS_ACCORDIONTITLECONTAINEREXTENSION_H

#include "ContainerExtension.h"
#include "AccordionTitleContainer.h"

class AccordionTitleContainerExtension: public ContainerExtension {
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)
public:
    explicit AccordionTitleContainerExtension(UI::AccordionTitleContainer* container, QObject* parent = nullptr);
};


#endif //CLOEXTENSIONS_ACCORDIONTITLECONTAINEREXTENSION_H