#include "PatternImportDialog.h"
#include "ui_PatternImportDialog.h"

#include "CLOAPIInterface.h"

using namespace UI;

PatternImportDialog::PatternImportDialog(Chrysalis::Project* project, ParametersModel* model, ParametersDelegate* delegate)
    : model_(model), project_(project), ui(new Ui::PatternImportDialog) {
    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);
    ui->baseDialogContainer->install({ui->content, ui->footer});

    ui->parametersListView->setModel(model_);
    ui->parametersListView->setItemDelegate(delegate);

    const int space = ui->parametersListView->spacing();

    int totalHeight = space;
    for (int i = 0; i < model_->rowCount({}); i++) {
        ui->parametersListView->openPersistentEditor(model_->index(i));
        totalHeight += delegate->sizeHint({}, model->index(i)).height() + 2 * space;
    }
    ui->parametersListView->setFixedHeight(std::min(totalHeight, ui->parametersListView->maximumHeight()));
}

PatternImportDialog::~PatternImportDialog() {
    delete ui;
    delete model_;
    delete project_;
}