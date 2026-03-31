#ifndef CLOEXTENSIONS_TAB_H
#define CLOEXTENSIONS_TAB_H

#include <QTabWidget>

namespace CloUICommon {
    class Tab : public QTabWidget
    {
        Q_OBJECT
    public:
        explicit Tab(QWidget* parent = nullptr) : QTabWidget(parent) {}
    };
}

#endif //CLOEXTENSIONS_TAB_H