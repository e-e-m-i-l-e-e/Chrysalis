#include "AccordionContainerExtension.h"

#include "Logger.h"

AccordionContainerExtension::AccordionContainerExtension(UI::Accordion *widget, QObject *parent)
    : ContainerExtension(parent), accordion_(widget) {}

int AccordionContainerExtension::count() const
{
    return 2;  // slot 0 = titleWidget, slot 1 = contentWidget
}

QWidget *AccordionContainerExtension::widget(int index) const
{
    LOG_DEBUG("Getting widget: {}. Class: {}", index, this->metaObject()->className());
    switch (index) {
        case 0:  return accordion_->titleWidget();
        case 1:  return accordion_->contentWidget();
        default: return nullptr;
    }
}

void AccordionContainerExtension::addWidget(QWidget *widget)
{
    LOG_DEBUG("Adding widget: {}. Class: {}", widget->objectName().toStdString(), this->metaObject()->className());
    // Designer calls addWidget() sequentially for each child declared in domXml.
    // Using m_currentIndex (always 0) would send both children to slot 0.
    // m_nextFillIndex advances slot-by-slot so title gets 0 and content gets 1.
    if (m_nextFillIndex < count()) {
        insertWidget(m_nextFillIndex, widget);
        m_nextFillIndex++;
    }
}

void AccordionContainerExtension::insertWidget(int index, QWidget *widget)
{
    LOG_DEBUG("Inserting widget: {}", index);
    switch (index) {
        case 0: accordion_->setTitleWidget(widget);   break;
        case 1: accordion_->setContentWidget(widget); break;
        default: break;
    }
}
