#ifndef CHRYSALIS_BASEINSERTABLECONTAINER_H
#define CHRYSALIS_BASEINSERTABLECONTAINER_H

#include "BaseContainer.h"

namespace UI {
    class BaseInsertableContainer: public QWidget, public BaseContainer {
    protected:
        explicit BaseInsertableContainer(QWidget *parent): QWidget(parent), BaseContainer() {}
    public:
        virtual void remove(int index) = 0;
    };
}

#endif //CHRYSALIS_BASEINSERTABLECONTAINER_H