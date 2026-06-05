#ifndef CHRYSALIS_PATTERNIMPORTDIALOG_H
#define CHRYSALIS_PATTERNIMPORTDIALOG_H

#include "Project.h"
#include "BaseDialog.h"
#include "ParametersModel.h"
#include "ParametersDelegate.h"

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class PatternImportDialog;
    }
    QT_END_NAMESPACE

    class PatternImportDialog: public BaseDialog {
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