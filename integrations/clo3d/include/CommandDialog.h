#ifndef CHRYSALIS_COMMANDDIALOG_H
#define CHRYSALIS_COMMANDDIALOG_H

#include "BaseCommand.h"
#include "BaseCommandArgumentsWidget.h"
#include "BaseDialog.h"

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class CommandDialog;
    }
    QT_END_NAMESPACE

    class CommandDialog: public BaseDialog {
        Q_OBJECT
    public:
        explicit CommandDialog(const QString& title, BaseCommandArgumentsWidget* argumentsWidget, BaseCommand* command);
        ~CommandDialog() override;

        void accept() override;
    private:
        Ui::CommandDialog* ui;
        /// @uml{composition}
        BaseCommand* command_;
        /// @uml{composition}
        BaseCommandArgumentsWidget* argumentsWidget_;
    };
} // UI

#endif //CHRYSALIS_COMMANDDIALOG_H