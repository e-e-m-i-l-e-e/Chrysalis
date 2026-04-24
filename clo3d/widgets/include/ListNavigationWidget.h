#ifndef FASHIONDESIGNAPPS_LISTNAVIGATIONWIDGET_H
#define FASHIONDESIGNAPPS_LISTNAVIGATIONWIDGET_H

#include "BaseInsertableContainer.h"

namespace UI {
    QT_BEGIN_NAMESPACE

namespace Ui {
        class ListNavigationWidget;
    }

    QT_END_NAMESPACE

    class ListNavigationWidget: public BaseInsertableContainer {
        Q_OBJECT
    public:
        explicit ListNavigationWidget(QWidget *parent = nullptr);
        ~ListNavigationWidget() override;

        int count() const override;
        void remove(int index) override;
        void insertWidget(int index, QWidget *widget) override;
        [[nodiscard]] QWidget* getWidget(int index) override;
    private:
        Ui::ListNavigationWidget *ui;
    };
}

#endif //FASHIONDESIGNAPPS_LISTNAVIGATIONWIDGET_H