#ifndef CLOEXTENSIONS_ACCORDION_H
#define CLOEXTENSIONS_ACCORDION_H

#include <QWidget>

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Accordion; }
    QT_END_NAMESPACE

    class Accordion : public QWidget {
        Q_OBJECT

    public:
        explicit Accordion(QWidget *parent = nullptr);
        ~Accordion() override;

        // Accessors for the container extension
        QWidget *titleWidget()   const;
        QWidget *contentWidget() const;

        // Called by AccordionContainerExtension::insertWidget()
        void setTitleWidget(QWidget *w);
        void setContentWidget(QWidget *w);

    private:
        Ui::Accordion *ui;
        QWidget *m_titleWidget   = nullptr;
        QWidget *m_contentWidget = nullptr;
    };
} // namespace UI

#endif //CLOEXTENSIONS_ACCORDION_H
