#ifndef CLOEXTENSIONS_TAB_H
#define CLOEXTENSIONS_TAB_H

#include <QTabWidget>

namespace CloUICommon {
    class Tab : public QTabWidget
    {
        Q_OBJECT
    public:
        explicit Tab(QWidget* parent = nullptr);
    };
}

#endif //CLOEXTENSIONS_TAB_H