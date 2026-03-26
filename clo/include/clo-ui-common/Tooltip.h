#ifndef CLOEXTENSIONS_TOOLTIP_H
#define CLOEXTENSIONS_TOOLTIP_H

#include <QWidget>

namespace CloUICommon {
    class Tooltip : public QWidget
    {
        Q_OBJECT
    public:
        explicit Tooltip(QWidget* parent = nullptr) : QWidget(parent) {}
    };
}

#endif //CLOEXTENSIONS_TOOLTIP_H