#include "BaseDialog.h"

using namespace UI;

BaseDialog::BaseDialog(): QDialog() {
    setWindowModality(Qt::WindowModal);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    connect(this, &QDialog::accepted, this, &QDialog::deleteLater);
    connect(this, &QDialog::rejected, this, &QDialog::deleteLater);
}
