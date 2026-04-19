#ifndef CLOEXTENSIONS_CONTAINER_H
#define CLOEXTENSIONS_CONTAINER_H

#include <QWidget>

namespace UI {
    class BaseContainer: public QWidget {
    protected:
        explicit BaseContainer(QWidget* parent);
    public:
        void install(const QList<QWidget*>& widgets);
        virtual void insertWidget(int index, QWidget* widget) = 0;
        [[nodiscard]] virtual QWidget* getWidget(int index) = 0;
    };
}

#endif //CLOEXTENSIONS_CONTAINER_H