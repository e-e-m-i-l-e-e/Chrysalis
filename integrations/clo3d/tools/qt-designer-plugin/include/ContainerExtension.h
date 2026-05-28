#ifndef CHRYSALIS_CONTAINEREXTENSION_H
#define CHRYSALIS_CONTAINEREXTENSION_H

#include <QDesignerContainerExtension>

#include "BaseContainer.h"

#define LOGGER_NAME "Container Extension"

class ContainerExtension: public QObject, public QDesignerContainerExtension {
protected:
    explicit ContainerExtension(UI::BaseContainer* container, QObject* parent);
public:
    int count() const override; // NOLINT(*-use-nodiscard)
    QWidget* widget(int index) const override; // NOLINT(*-use-nodiscard)
    int currentIndex() const override; // NOLINT(*-use-nodiscard)
    void setCurrentIndex(int index) override;
    void addWidget(QWidget *widget) override;
    void insertWidget(int index, QWidget *widget) override;
    void remove(int index) override;
    bool canAddWidget() const override; // NOLINT(*-use-nodiscard)
    bool canRemove(int index) const override; // NOLINT(*-use-nodiscard)
private:
    int index_ {};
    UI::BaseContainer* container_;
};

#endif //CHRYSALIS_CONTAINEREXTENSION_H