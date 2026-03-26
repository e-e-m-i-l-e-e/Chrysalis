#ifndef CLOEXTENSIONS_SCROLLAREA_H
#define CLOEXTENSIONS_SCROLLAREA_H

#include <CLOAPIInterface.h>
#include <QScrollArea>

namespace CloUICommon {
    class ScrollArea : public QScrollArea
    {
        Q_OBJECT
    public:
        explicit ScrollArea(QWidget* parent = nullptr) : QScrollArea(parent) {
            UTILITY_API->UpdateCloStyleForPlugIn(this);
        }
    };
}

#endif //CLOEXTENSIONS_SCROLLAREA_H