#ifndef FASHIONDESIGNAPPS_LISTNAVIGATIONEXTENSION_H
#define FASHIONDESIGNAPPS_LISTNAVIGATIONEXTENSION_H

#include "ListNavigationWidget.h"
#include "InsertableContainerExtension.h"

class ListNavigationWidgetExtension: public InsertableContainerExtension {
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)
public:
    explicit ListNavigationWidgetExtension(UI::ListNavigationWidget* container, QObject* parent)
        : InsertableContainerExtension(container, parent) {}
};


#endif //FASHIONDESIGNAPPS_LISTNAVIGATIONEXTENSION_H