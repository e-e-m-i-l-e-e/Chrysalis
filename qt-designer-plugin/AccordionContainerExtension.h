#ifndef CLOEXTENSIONS_ACCORDIONCONTAINEREXTENSION_H
#define CLOEXTENSIONS_ACCORDIONCONTAINEREXTENSION_H

#include "ContainerExtension.h"
#include "AccordionContainer.h"

class AccordionContainerExtension: public ContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    explicit AccordionContainerExtension(UI::AccordionContainer* widget, QObject *parent, int count);
};

#endif //CLOEXTENSIONS_ACCORDIONCONTAINEREXTENSION_H