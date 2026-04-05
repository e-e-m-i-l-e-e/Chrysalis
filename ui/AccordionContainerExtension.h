#ifndef CLOEXTENSIONS_ACCORDIONCONTAINEREXTENSION_H
#define CLOEXTENSIONS_ACCORDIONCONTAINEREXTENSION_H

#include <QDesignerContainerExtension>

#include "Accordion.h"

class AccordionContainerExtension : public QObject,
                                    public QDesignerContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    explicit AccordionContainerExtension(UI::Accordion* widget, QObject *parent);

    // --- QDesignerContainerExtension interface ---
    ~AccordionContainerExtension() override;

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
    UI::Accordion *accordion_;
    int m_currentIndex = 0;   // active page shown in Designer's navigator
    int m_nextFillIndex = 0;  // tracks next slot when addWidget() is called sequentially
};

#endif //CLOEXTENSIONS_ACCORDIONCONTAINEREXTENSION_H