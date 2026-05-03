#ifndef FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H
#define FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H

#include <functional>

#include <QDialog>

#include "ExtensionsSettings.h"
#include "BaseExtensionsSettingsPageWidget.h"

namespace UI {

    QT_BEGIN_NAMESPACE
    namespace Ui {
        class ExtensionsSettingsDialog;
    }
    QT_END_NAMESPACE

    /// @uml{note[top] UI is constructed on menu option triggered and destroyed on "Close".}
    class ExtensionsSettingsDialog : public QDialog {
        Q_OBJECT
    public:
        explicit ExtensionsSettingsDialog(const std::shared_ptr<ExtensionsSettings> &settings, QWidget *parent = nullptr);
        ~ExtensionsSettingsDialog() override;

        void accept() override;
        void reject() override;
        int exec() override;

        void addPage(BaseExtensionsSettingsPageWidget* page) const;
    private:
        void processPages(const std::function<void(BaseExtensionsSettingsPageWidget*)> &) const;

        Ui::ExtensionsSettingsDialog *ui;
        std::shared_ptr<ExtensionsSettings> extensionsSettings;
    };
} // UI

#endif //FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H