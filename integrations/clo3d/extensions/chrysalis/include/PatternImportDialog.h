#ifndef CHRYSALIS_PATTERNIMPORTDIALOG_H
#define CHRYSALIS_PATTERNIMPORTDIALOG_H

#include <QDialog>

#include "Project.h"
#include "ParametersModel.h"
#include "ParametersDelegate.h"

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class PatternImportDialog;
    }
    QT_END_NAMESPACE

    class PatternImportDialog : public QDialog {
        Q_OBJECT
    public:
        explicit PatternImportDialog(Chrysalis::Project* project, ParametersModel* model, ParametersDelegate* delegate, QWidget* parent = nullptr);
        ~PatternImportDialog() override;

    private:
        ParametersModel* model_;
        Chrysalis::Project* project_;

        Ui::PatternImportDialog* ui;
    };
} // UI

#endif //CHRYSALIS_PATTERNIMPORTDIALOG_H