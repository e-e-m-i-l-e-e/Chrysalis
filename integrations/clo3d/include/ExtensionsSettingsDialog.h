#ifndef CHRYSALIS_EXTENSIONSSETTINGSDIALOG_H
#define CHRYSALIS_EXTENSIONSSETTINGSDIALOG_H

#include <functional>

#include <QDialog>

#include "BaseExtensionSettingsWidget.h"

namespace UI {

    QT_BEGIN_NAMESPACE
    namespace Ui {
        class ExtensionsSettingsDialog;
    }
    QT_END_NAMESPACE

    class ExtensionsSettingsDialog : public QDialog {
        Q_OBJECT
    public:
        explicit ExtensionsSettingsDialog(ExtensionsSettings* settings, QWidget *parent = nullptr);
        ~ExtensionsSettingsDialog() override;

        void accept() override;
        void reject() override;
        int exec() override;

        void addPage(BaseExtensionSettingsWidget* page) const;
    public slots:
        void reset();
    private:
        void processPages(void(BaseExtensionSettingsWidget::*processor)()) const;

        Ui::ExtensionsSettingsDialog *ui;
        ExtensionsSettings* extensionsSettings;
    };
} // UI

#endif //CHRYSALIS_EXTENSIONSSETTINGSDIALOG_H