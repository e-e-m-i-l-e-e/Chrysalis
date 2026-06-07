#ifndef CHRYSALIS_PATTERNIMPORTDIALOG_H
#define CHRYSALIS_PATTERNIMPORTDIALOG_H

#include "Project.h"
#include "BaseDialog.h"
#include "ParametrsModel.h"
#include "PatternImporter.h"
#include "ParameterWidget.h"
#include "ParameterDelegate.h"

namespace UI
{
    QT_BEGIN_NAMESPACE

    namespace Ui
    {
        class PatternImportDialog;
    }

    QT_END_NAMESPACE

    class PatternImportDialog : public BaseDialog
    {
        Q_OBJECT

    public:
        explicit PatternImportDialog(Chrysalis::PatternImporter* importer, ParametersModel* model,
                                     ParameterDelegate* delegate);
        ~PatternImportDialog() override;

        void accept() override;

    private:
        Ui::PatternImportDialog* ui;
        /// @uml{composition}
        Chrysalis::PatternImporter* importer_;
        /// @uml{composition}
        ParametersModel* model_;
        /// @uml{composition}
        ParameterDelegate* delegate_;
    };
} // UI

#endif //CHRYSALIS_PATTERNIMPORTDIALOG_H
