#ifndef CLOEXTENSIONS_TABLECONTENTEXTENSION_H
#define CLOEXTENSIONS_TABLECONTENTEXTENSION_H

#include "ContainerExtension.h"
#include "TableContentContainer.h"


class TableContentContainerExtension: public ContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    explicit TableContentContainerExtension(UI::TableContentContainer* widget, QObject *parent);
};


#endif //CLOEXTENSIONS_TABLECONTENTEXTENSION_H