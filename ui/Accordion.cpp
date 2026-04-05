#include "Accordion.h"
#include "ui_Accordion.h"

#include <QVBoxLayout>

namespace UI {

    Accordion::Accordion(QWidget *parent) : QWidget(parent), ui(new Ui::Accordion)
    {
        ui->setupUi(this);

        // Pre-create placeholder widgets so widget() never returns null or accordion_ itself.
        // Designer will replace these via setTitleWidget / setContentWidget
        // once it processes the domXml child declarations.
        m_titleWidget = new QWidget(this);
        ui->titleLayout->addWidget(m_titleWidget, 0, 0);

        m_contentWidget = new QWidget(this);
        ui->contentLayout->addWidget(m_contentWidget, 0, 0);
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
