#ifndef CHRYSALIS_BASEDIALOGCONTAINER_H
#define CHRYSALIS_BASEDIALOGCONTAINER_H

#include <QDialog>

#include "BaseContainer.h"

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class BaseDialogContainer;
    }
    QT_END_NAMESPACE

    class BaseDialogContainer: public QDialog, public BaseContainer {
        Q_OBJECT
    public:
        explicit BaseDialogContainer(QWidget* parent = nullptr);
        ~BaseDialogContainer() override;

        [[nodiscard]] int count() const override;
        void insertWidget(int index, QWidget* widget) override;
        [[nodiscard]] QWidget* getWidget(int index) override;
    private:
        Ui::BaseDialogContainer* ui;
    };
} // UI

#endif //CHRYSALIS_BASEDIALOGCONTAINER_H