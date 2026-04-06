#ifndef CLOEXTENSIONS_CONTAINEREXTENSION_H
#define CLOEXTENSIONS_CONTAINEREXTENSION_H

#include <QDesignerContainerExtension>

#define LOGGER_NAME "Container Extension"

class ContainerExtension: public QObject, public QDesignerContainerExtension {
protected:
    explicit ContainerExtension(QObject* parent);
public:
    int currentIndex() const override; // NOLINT(*-use-nodiscard)
    void setCurrentIndex(int index) override;
    void remove(int index) override;
    bool canAddWidget() const override; // NOLINT(*-use-nodiscard)
    bool canRemove(int index) const override; // NOLINT(*-use-nodiscard)
private:
    int currentIndex_ = 0;
};

#endif //CLOEXTENSIONS_CONTAINEREXTENSION_H