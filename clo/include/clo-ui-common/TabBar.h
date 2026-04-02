#ifndef CLOEXTENSIONS_TABBAR_H
#define CLOEXTENSIONS_TABBAR_H

#include <QTabBar>

namespace CloUICommon {
    class TabBar : public QTabBar
    {
        Q_OBJECT
    public:
        explicit TabBar(QWidget* parent = nullptr);
    };
}

#endif //CLOEXTENSIONS_TABBAR_H