#ifndef FASHIONDESIGNAPPS_LISTNAVIGATIONWIDGET_H
#define FASHIONDESIGNAPPS_LISTNAVIGATIONWIDGET_H

#include <QWidget>

namespace UI {
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

        void addPage(QWidget* page) const;
    private:
        Ui::ListNavigationWidget *ui;
    };
}

#endif //FASHIONDESIGNAPPS_LISTNAVIGATIONWIDGET_H