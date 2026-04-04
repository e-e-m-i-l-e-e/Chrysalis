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

        Q_PROPERTY(QString title READ getTitle WRITE setTitle)

    public:
        explicit Accordion(QWidget *parent = nullptr);

        ~Accordion() override;

        QString getTitle() const;
        void setTitle(const QString &title) const;

    private:
        Ui::Accordion *ui;
    };
} // UI

#endif //CLOEXTENSIONS_ACCORDION_H