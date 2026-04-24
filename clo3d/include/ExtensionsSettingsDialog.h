//
// Created by emily on 24/04/2026.
//

#ifndef FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H
#define FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H

#include <QDialog>

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

        void addPage(QWidget* page) const;
    private:
        Ui::ExtensionsSettingsDialog *ui;
    };
} // UI

#endif //FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H