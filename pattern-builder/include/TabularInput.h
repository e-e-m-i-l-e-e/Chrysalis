//
// Created by emily on 03/04/2026.
//

#ifndef CLOEXTENSIONS_TABULARINPUT_H
#define CLOEXTENSIONS_TABULARINPUT_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class TabularInput;
}

QT_END_NAMESPACE

class TabularInput : public QWidget {
    Q_OBJECT

public:
    explicit TabularInput(QWidget *parent = nullptr);

    ~TabularInput() override;

private:
    Ui::TabularInput *ui;
};


#endif //CLOEXTENSIONS_TABULARINPUT_H