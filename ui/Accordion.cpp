#include "Accordion.h"
#include "ui_Accordion.h"

#include <QVBoxLayout>

namespace UI {

    Accordion::Accordion(QWidget *parent) : QWidget(parent), ui(new Ui::Accordion)
    {
        ui->setupUi(this);
    }

    Accordion::~Accordion()
    {
        delete ui;
    }

    QWidget *Accordion::titleWidget()   const { return m_titleWidget; }
    QWidget *Accordion::contentWidget() const { return m_contentWidget; }

    void Accordion::setTitleWidget(QWidget *w)
    {
        if (m_titleWidget) {
            ui->titleLayout->removeWidget(m_titleWidget);
            m_titleWidget->deleteLater();   // safe: we created it, Designer has no reference to it
        }
        m_titleWidget = w;
        if (w)
            ui->titleLayout->addWidget(w, 0, 0);
    }

    void Accordion::setContentWidget(QWidget *w)
    {
        if (m_contentWidget) {
            ui->contentLayout->removeWidget(m_contentWidget);
            m_contentWidget->deleteLater();
        }
        m_contentWidget = w;
        if (w)
            ui->contentLayout->addWidget(w, 0, 0);
    }

} // namespace UI
