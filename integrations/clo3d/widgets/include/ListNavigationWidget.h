#ifndef CHRYSALIS_LISTNAVIGATIONWIDGET_H
#define CHRYSALIS_LISTNAVIGATIONWIDGET_H

#include "NamedWidget.h"

namespace CLO3D::UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class ListNavigationWidget;
    }
    QT_END_NAMESPACE

    class ListNavigationWidget: public QWidget {
        Q_OBJECT
    public:
        explicit ListNavigationWidget(QWidget *parent = nullptr);
        ~ListNavigationWidget() override;

        [[nodiscard]] int count() const;
        void addPage(NamedWidget* page) const;
        [[nodiscard]] NamedWidget* getPage(int index) const;

    private:
        Ui::ListNavigationWidget *ui;
    };
}

#endif //CHRYSALIS_LISTNAVIGATIONWIDGET_H