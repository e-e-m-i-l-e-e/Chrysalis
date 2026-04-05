#ifndef CLOEXTENSIONS_ACCORDIONTITLECONTAINER_H
#define CLOEXTENSIONS_ACCORDIONTITLECONTAINER_H

#include <QWidget>

class AccordionTitleContainerExtension;

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class AccordionTitleContainer;
    }

    QT_END_NAMESPACE

    class AccordionTitleContainer : public QWidget {
        Q_OBJECT
        Q_PROPERTY(QString title READ getTitle WRITE setTitle)

        friend class ::AccordionTitleContainerExtension;

    public:
        explicit AccordionTitleContainer(QWidget *parent = nullptr);

        ~AccordionTitleContainer() override;

        QString getTitle() const;
        void setTitle(const QString& title) const;

    private:

        void setCustomWidget(QWidget *widget) const;
        QWidget* getCustomWidget() const;

        Ui::AccordionTitleContainer *ui;
    };
}

#endif //CLOEXTENSIONS_ACCORDIONTITLECONTAINER_H