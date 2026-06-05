#ifndef CHRYSALIS_BASEDIALOGCONTAINEREXTENSION_H
#define CHRYSALIS_BASEDIALOGCONTAINEREXTENSION_H

#include "ContainerExtension.h"
#include "BaseDialogContainer.h"

class BaseDialogContainerExtension : public ContainerExtension {
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)
public:
    explicit BaseDialogContainerExtension(UI::BaseDialogContainer* container, QObject* parent)
        : ContainerExtension(container, parent) {}
};

#endif //CHRYSALIS_BASEDIALOGCONTAINEREXTENSION_H