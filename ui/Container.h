#ifndef CLOEXTENSIONS_CONTAINER_H
#define CLOEXTENSIONS_CONTAINER_H

#include <QWidget>

namespace UI {
    class Container: public QWidget {
    protected:
        explicit Container(QWidget* parent);
        virtual QLayout* getLayout() = 0;
    public:
        int count() const; // NOLINT(*-use-nodiscard)
        void insertWidget(int index, QWidget* widget);
        [[nodiscard]] QWidget* getWidget(int index) const;
    private:
        QList<QWidget*> customWidgets;
    };
}

#endif //CLOEXTENSIONS_CONTAINER_H