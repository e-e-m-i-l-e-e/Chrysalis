#ifndef CHRYSALIS_CONTAINER_H
#define CHRYSALIS_CONTAINER_H

#include <QWidget>

namespace CLO3D::UI {
    class BaseContainer {
    protected:
        BaseContainer() = default;
        virtual ~BaseContainer() = default;

    public:
        [[nodiscard]] virtual int count() const = 0;
        virtual void insertWidget(int index, QWidget* widget) = 0;
        [[nodiscard]] virtual QWidget* getWidget(int index) = 0;

        void install(const QList<QWidget*>& widgets) {
            for (int i = 0; i < widgets.length(); i++) {
                insertWidget(i, widgets.at(i));
            }
        }
    };
}

#endif //CHRYSALIS_CONTAINER_H