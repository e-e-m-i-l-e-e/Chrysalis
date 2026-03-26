#ifndef CLOEXTENSIONS_ICONBUTTON_H
#define CLOEXTENSIONS_ICONBUTTON_H

#include <QToolButton>

namespace CloUICommon {
    class IconButton : public QToolButton
    {
        Q_OBJECT
    public:
        explicit IconButton(QWidget* parent = nullptr) : QToolButton(parent) {}
    };
}

#endif //CLOEXTENSIONS_ICONBUTTON_H