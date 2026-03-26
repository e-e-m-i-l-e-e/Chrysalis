#ifndef CLOEXTENSIONS_TITLEBAR_H
#define CLOEXTENSIONS_TITLEBAR_H

#include <QWidget>

namespace CloUICommon {
    class TitleBar : public QWidget
    {
        Q_OBJECT
    public:
        explicit TitleBar(QWidget* parent = nullptr) : QWidget(parent) {}
    };
}

#endif //CLOEXTENSIONS_TITLEBAR_H