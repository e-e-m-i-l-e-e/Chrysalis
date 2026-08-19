#ifndef CHRYSALIS_INSERTABLECONTAINER_H
#define CHRYSALIS_INSERTABLECONTAINER_H

#include "ContainerExtension.h"
#include "BaseInsertableContainer.h"

namespace CLO3D::UI {
    class InsertableContainerExtension: public ContainerExtension {
    protected:
        explicit InsertableContainerExtension(BaseInsertableContainer* container, QObject* parent);
    public:
        int count() const override;
        QWidget* widget(int index) const override; // NOLINT(*-use-nodiscard)
        int currentIndex() const override;
        void setCurrentIndex(int index) override;
        void insertWidget(int index, QWidget *widget) override;
        void remove(int index) override;
        bool canAddWidget() const override;
        bool canRemove(int index) const override;
    private:
        int currentIndex_ = 0;
        BaseInsertableContainer* container_;
    };
}

#endif //CHRYSALIS_INSERTABLECONTAINER_H