#ifndef FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H
#define FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H

#include <QDialog>

#include "BaseExtensionsSettingsPageWidget.h"

namespace UI {

    QT_BEGIN_NAMESPACE
    namespace Ui {
        class ExtensionsSettingsDialog;
    }
    QT_END_NAMESPACE

    class ExtensionsSettingsDialog : public QDialog {
        Q_OBJECT
    public:
        explicit ExtensionsSettingsDialog(QWidget *parent = nullptr);
        ~ExtensionsSettingsDialog() override;

        void accept() override;
        void reject() override;

        void addPage(BaseExtensionsSettingsPageWidget* page) const;
    private:
        void processPages(void(*processor)(BaseExtensionsSettingsPageWidget*)) const;

        Ui::ExtensionsSettingsDialog *ui;
    };
} // UI

#endif //FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H