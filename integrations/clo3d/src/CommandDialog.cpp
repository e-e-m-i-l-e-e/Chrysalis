#include "CommandDialog.h"
#include "ui_CommandDialog.h"

#include "CLOAPIInterface.h"

using namespace CLO3D::UI;

CommandDialog::CommandDialog(const QString& title, BaseCommandArgumentsWidget* argumentsWidget, BaseCommand* command)
    : ui(new Ui::CommandDialog), command_(command), argumentsWidget_(argumentsWidget) {
    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);
    ui->baseDialogContainer->setTitle(title);
    ui->baseDialogContainer->install({ui->content, ui->footer});
    ui->argumentsWidgetWrapper->layout()->addWidget(argumentsWidget_);
    argumentsWidget_->load();
}

void CommandDialog::accept() {
    argumentsWidget_->save();
    command_->run();
    BaseDialog::accept();
}

CommandDialog::~CommandDialog() {
    delete ui;
    delete command_;
    delete argumentsWidget_;
}
