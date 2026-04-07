#ifndef CLOEXTENSIONS_CONTAINER_H
#define CLOEXTENSIONS_CONTAINER_H

#include <QWidget>
#include <QBoxLayout>

namespace UI {
    class Container: public QWidget {
    protected:
        explicit Container(QWidget* parent);
        virtual QBoxLayout* getLayout() = 0;
    public:
        void insertWidget(int index, QWidget* widget);
        [[nodiscard]] QWidget* getWidget(int index);
    };
}

#endif //CLOEXTENSIONS_CONTAINER_H