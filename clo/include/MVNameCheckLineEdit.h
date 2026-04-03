#ifndef CLOEXTENSIONS_MVNAMECHECKLINEEDIT_H
#define CLOEXTENSIONS_MVNAMECHECKLINEEDIT_H

#include <QLineEdit>

class MVNameCheckLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit MVNameCheckLineEdit(QWidget* parent = nullptr) : QLineEdit(parent) {}
};

#endif //CLOEXTENSIONS_MVNAMECHECKLINEEDIT_H