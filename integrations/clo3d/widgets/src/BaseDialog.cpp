#include "BaseDialog.h"

using namespace UI;

BaseDialog::BaseDialog(QWidget* parent): QDialog(parent) {
    setWindowModality(Qt::WindowModal);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}
