#ifndef CLOEXTENSIONS_ACCORDION_H
#define CLOEXTENSIONS_ACCORDION_H

#include <QWidget>

namespace CloUICommon {
    class Accordion : public QWidget
    {
        Q_OBJECT
    public:
        explicit Accordion(QWidget* parent = nullptr) : QWidget(parent) {}
    };
}

#endif //CLOEXTENSIONS_ACCORDION_H