#include "AccordionContainerExtension.h"

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
    // FIX 2: never return nullptr — Designer dereferences this immediately
    switch (index) {
        case 0:  return accordion_->titleWidget();
        case 1:  return accordion_->contentWidget();
        default: return accordion_->contentWidget();
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
    insertWidget(m_currentIndex, widget);
}

void AccordionContainerExtension::insertWidget(int index, QWidget *widget)
{
    // if (auto *slot = this->widget(index))
    //     if (auto *l = slot->layout())
    //         l->addWidget(widget);
}

void AccordionContainerExtension::remove(int /*index*/)
{
}

bool AccordionContainerExtension::canAddWidget() const
{
    return true;
}

bool AccordionContainerExtension::canRemove(int /*index*/) const
{
    return false;
}
