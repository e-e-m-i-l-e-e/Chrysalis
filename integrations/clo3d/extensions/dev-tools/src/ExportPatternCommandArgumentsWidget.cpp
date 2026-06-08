#include "ExportPatternCommandArgumentsWidget.h"
#include "ui_ExportPatternCommandArgumentsWidget.h"

#include <QFileDialog>

using namespace UI;

ExportPatternCommandArgumentsWidget::ExportPatternCommandArgumentsWidget(ExportPatternCommandArguments* arguments)
    : BaseCommandArgumentsWidget(arguments), ui(new Ui::ExportPatternCommandArgumentsWidget) {
    ui->setupUi(this);
    connect(ui->fileButton, &QToolButton::clicked, this, [this] {
        const auto fileName = QFileDialog::getSaveFileName(this, "Save Configuration", ui->fileName->text(), "JSON Files (*.json)");
        if (fileName.isEmpty()) return;
        ui->fileName->setText(fileName);
    });
}

ExportPatternCommandArgumentsWidget::~ExportPatternCommandArgumentsWidget() {
    delete ui;
}

void ExportPatternCommandArgumentsWidget::load() {
    BaseCommandArgumentsWidget::load();
    ui->fileName->setText(dynamic_cast<ExportPatternCommandArguments*>(arguments_)->getFilePath());
}

void ExportPatternCommandArgumentsWidget::save() const {
    dynamic_cast<ExportPatternCommandArguments*>(arguments_)->setFilePath(ui->fileName->text());
    BaseCommandArgumentsWidget::save();
}
