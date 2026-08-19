#include "BaseDialog.h"

using namespace CLO3D::UI;

BaseDialog::BaseDialog() {
    setWindowModality(Qt::WindowModal);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    connect(this, &QDialog::accepted, this, &QDialog::deleteLater);
    connect(this, &QDialog::rejected, this, &QDialog::deleteLater);
}
