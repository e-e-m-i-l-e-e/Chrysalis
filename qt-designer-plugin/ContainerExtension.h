#ifndef CLOEXTENSIONS_CONTAINEREXTENSION_H
#define CLOEXTENSIONS_CONTAINEREXTENSION_H

#include <QDesignerContainerExtension>

#include "Container.h"

#define LOGGER_NAME "Container Extension"

class ContainerExtension: public QObject, public QDesignerContainerExtension {
protected:
    explicit ContainerExtension(UI::Container* container, QObject* parent, int count);
    explicit ContainerExtension(UI::Container* container, QObject* parent, QVector<int> indexes);
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
    UI::Container* container_;

    QVector<int> indexes_;
    QVectorIterator<int> it_;
};

#endif //CLOEXTENSIONS_CONTAINEREXTENSION_H