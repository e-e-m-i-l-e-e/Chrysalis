#ifndef CHRYSALIS_PATTERNIMPORTDIALOG_H
#define CHRYSALIS_PATTERNIMPORTDIALOG_H

#include "Project.h"
#include "BaseDialog.h"
#include "BaseDelegate.h"
#include "BaseListModel.h"
#include "PatternImporter.h"
#include "ParameterWidget.h"

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class PatternImportDialog;
    }
    QT_END_NAMESPACE

    class PatternImportDialog: public BaseDialog {
        Q_OBJECT
    public:
        explicit PatternImportDialog(Chrysalis::PatternImporter* importer,
                                     BaseModel<Chrysalis::ParametersContainer>* model,
                                     BaseDelegate<ParameterWidget, Chrysalis::Parameter>* delegate);
        ~PatternImportDialog() override;

        void accept() override;
    private:
        Ui::PatternImportDialog* ui;
        /// @uml{composition}
        Chrysalis::PatternImporter* importer_;
        /// @uml{composition}
        BaseModel<Chrysalis::ParametersContainer>* model_;
        BaseDelegate<ParameterWidget, Chrysalis::Parameter>* delegate_;
    };
} // UI

#endif //CHRYSALIS_PATTERNIMPORTDIALOG_H