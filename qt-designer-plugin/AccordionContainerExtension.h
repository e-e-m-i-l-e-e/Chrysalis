#ifndef CLOEXTENSIONS_ACCORDIONCONTAINEREXTENSION_H
#define CLOEXTENSIONS_ACCORDIONCONTAINEREXTENSION_H

#include "ContainerExtension.h"
#include "Accordion.h"

class AccordionContainerExtension: public ContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    explicit AccordionContainerExtension(UI::Accordion* widget, QObject *parent);

    int count() const override;

    QWidget * widget(int index) const override;

    void addWidget(QWidget *widget) override;

    void insertWidget(int index, QWidget *widget) override;

private:
    UI::Accordion *accordion_;
    int m_nextFillIndex = 0;  // tracks next slot when addWidget() is called sequentially
};

#endif //CLOEXTENSIONS_ACCORDIONCONTAINEREXTENSION_H