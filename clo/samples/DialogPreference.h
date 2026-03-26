#ifndef CLOEXTENSIONS_DIALOGPREFERENCE_H
#define CLOEXTENSIONS_DIALOGPREFERENCE_H

#include "MVDialog.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class DialogPreference;
}

QT_END_NAMESPACE

class DialogPreference : public MVDialog {
    Q_OBJECT

public:
    explicit DialogPreference(QWidget *parent = nullptr);

    ~DialogPreference() override;

private:
    Ui::DialogPreference *ui;
};


#endif //CLOEXTENSIONS_DIALOGPREFERENCE_H