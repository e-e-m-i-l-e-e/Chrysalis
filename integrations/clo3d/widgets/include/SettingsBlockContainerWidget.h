#ifndef CHRYSALIS_SETTINGSBLOCKCONTAINERWIDGET_H
#define CHRYSALIS_SETTINGSBLOCKCONTAINERWIDGET_H

#include "NamedWidget.h"
#include "BaseContainer.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class SettingsBlockContainerWidget;
    }

    QT_END_NAMESPACE

    class SettingsBlockContainerWidget: public NamedWidget, public BaseContainer {
        Q_OBJECT
    public:
        explicit SettingsBlockContainerWidget(QWidget *parent = nullptr);
        ~SettingsBlockContainerWidget() override;

        [[nodiscard]] int count() const override;
        void insertWidget(int index, QWidget *widget) override;
        [[nodiscard]] QWidget * getWidget(int index) override;

        void setTitle(const QString &title) override;

    private:
        Ui::SettingsBlockContainerWidget *ui;
    };
} // UI

#endif //CHRYSALIS_SETTINGSBLOCKCONTAINERWIDGET_H