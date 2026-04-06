#ifndef CLOEXTENSIONS_ACCORDIONTITLECONTAINEREXTENSION_H
#define CLOEXTENSIONS_ACCORDIONTITLECONTAINEREXTENSION_H

#include "ContainerExtension.h"
#include "AccordionTitleContainer.h"

class AccordionTitleContainerExtension: public ContainerExtension {
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:

    explicit AccordionTitleContainerExtension(UI::AccordionTitleContainer* container, QObject* parent = nullptr);

    int count() const override;

    QWidget * widget(int index) const override;

    void addWidget(QWidget *widget) override;

    void insertWidget(int index, QWidget *widget) override;

private:
    UI::AccordionTitleContainer* container_;
};


#endif //CLOEXTENSIONS_ACCORDIONTITLECONTAINEREXTENSION_H