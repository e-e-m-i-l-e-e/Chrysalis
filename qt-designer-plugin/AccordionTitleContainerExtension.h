#ifndef CLOEXTENSIONS_ACCORDIONTITLECONTAINEREXTENSION_H
#define CLOEXTENSIONS_ACCORDIONTITLECONTAINEREXTENSION_H

#include <QDesignerContainerExtension>

#include "AccordionTitleContainer.h"

class AccordionTitleContainerExtension: public QObject, public QDesignerContainerExtension {
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:

    explicit AccordionTitleContainerExtension(UI::AccordionTitleContainer* container, QObject* parent = nullptr);

    int count() const override;

    QWidget * widget(int index) const override;

    int currentIndex() const override;

    void setCurrentIndex(int index) override;

    void addWidget(QWidget *widget) override;

    void insertWidget(int index, QWidget *widget) override;

    void remove(int index) override;

    bool canAddWidget() const override;

    bool canRemove(int index) const override;

private:
    UI::AccordionTitleContainer* container_;
};


#endif //CLOEXTENSIONS_ACCORDIONTITLECONTAINEREXTENSION_H