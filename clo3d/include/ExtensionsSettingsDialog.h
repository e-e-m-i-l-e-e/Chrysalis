#ifndef FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H
#define FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H

#include <QDialog>

#include "NamedWidget.h"

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

        void addPage(NamedWidget* page) const;
    private:
        Ui::ExtensionsSettingsDialog *ui;
    };
} // UI

#endif //FASHIONDESIGNAPPS_EXTENSIONSSETTINGSDIALOG_H