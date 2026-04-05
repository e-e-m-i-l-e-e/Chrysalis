#ifndef CLOEXTENSIONS_ACCORDION_H
#define CLOEXTENSIONS_ACCORDION_H

#include <QWidget>

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class Accordion;
    }

    QT_END_NAMESPACE

    class Accordion : public QWidget {
        Q_OBJECT

    public:
        explicit Accordion(QWidget *parent = nullptr);

        ~Accordion() override;

        QWidget *titleWidget() const;
        QWidget *contentWidget() const;

    private:
        Ui::Accordion *ui;
    };
} // UI

#endif //CLOEXTENSIONS_ACCORDION_H