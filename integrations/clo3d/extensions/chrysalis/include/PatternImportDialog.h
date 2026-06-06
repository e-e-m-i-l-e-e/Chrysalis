#ifndef CHRYSALIS_PATTERNIMPORTDIALOG_H
#define CHRYSALIS_PATTERNIMPORTDIALOG_H

#include "Project.h"
#include "BaseDialog.h"
#include "PatternImporter.h"
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
        explicit PatternImportDialog(Chrysalis::PatternImporter* importer, ParametersModel* model, ParametersDelegate* delegate);
        ~PatternImportDialog() override;

        void accept() override;
    private:
        /// @uml{composition}
        ParametersModel* model_;
        /// @uml{composition}
        Chrysalis::PatternImporter* importer_;

        Ui::PatternImportDialog* ui;
    };
} // UI

#endif //CHRYSALIS_PATTERNIMPORTDIALOG_H