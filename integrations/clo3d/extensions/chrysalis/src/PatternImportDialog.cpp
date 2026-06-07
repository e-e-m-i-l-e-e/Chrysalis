#include "PatternImportDialog.h"
#include "ui_PatternImportDialog.h"

#include "CLOAPIInterface.h"
#include "PatternImporter.h"

using namespace UI;

PatternImportDialog::PatternImportDialog(Chrysalis::PatternImporter* importer, ParametersModel* model,
                                         ParameterDelegate* delegate)
    : ui(new Ui::PatternImportDialog), importer_(importer), model_(model), delegate_(delegate) {
    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);
    ui->baseDialogContainer->install({ui->content, ui->footer});

    ui->parametersListView->setModel(model_);
    ui->parametersListView->setItemDelegate(delegate_);

    const int space = ui->parametersListView->spacing();

    int totalHeight = space;
    for (int i = 0; i < model_->rowCount({}); i++) {
        ui->parametersListView->openPersistentEditor(model_->index(i));
        totalHeight += delegate_->sizeHint({}, model->index(i)).height() + 2 * space;
    }
    ui->parametersListView->setFixedHeight(std::min(totalHeight, ui->parametersListView->maximumHeight()));
}

PatternImportDialog::~PatternImportDialog() {
    delete ui;
    delete model_;
    delete importer_;
}

void PatternImportDialog::accept() {
    importer_->import();
    BaseDialog::accept();
}