#include "AccordionContainerExtension.h"

#include "QDebug"

AccordionContainerExtension::AccordionContainerExtension(UI::Accordion *widget, QObject *parent)
    : QObject(parent),        // FIX 1: pass parent to QObject — Designer owns this via parent chain
      accordion_(widget)
{
}

AccordionContainerExtension::~AccordionContainerExtension() = default;

int AccordionContainerExtension::count() const
{
    return 2;  // slot 0 = titleWidget, slot 1 = contentWidget
}

QWidget *AccordionContainerExtension::widget(int index) const
{
    switch (index) {
        case 0:  return accordion_->titleWidget();
        case 1:  return accordion_->contentWidget();
        default: return nullptr;
    }
}

int AccordionContainerExtension::currentIndex() const
{
    return m_currentIndex;  // FIX 3: was hardcoded to 1, out of range for count()
}

void AccordionContainerExtension::setCurrentIndex(int index)
{
    if (index >= 0 && index < count())
        m_currentIndex = index;
}

void AccordionContainerExtension::addWidget(QWidget *widget)
{
    qWarning() << "Accordion: Only BasicAccordionTitle allowed as title!";
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
    qWarning() << "INSERT Accordion: Only BasicAccordionTitle allowed as title!";
    switch (index) {
        case 0: accordion_->setTitleWidget(widget);   break;
        case 1: accordion_->setContentWidget(widget); break;
        default: break;
    }
}

void AccordionContainerExtension::remove(int /*index*/)
{
}

bool AccordionContainerExtension::canAddWidget() const
{
    return false;  // fixed 2-slot container — title and content only, no extra pages
}

bool AccordionContainerExtension::canRemove(int /*index*/) const
{
    return false;
}
