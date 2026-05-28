#ifndef CHRYSALIS_MVDOCKINGBUTTON_H
#define CHRYSALIS_MVDOCKINGBUTTON_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class MVDockingButton;
}

QT_END_NAMESPACE

class MVDockingButton : public QWidget {
    Q_OBJECT

public:
    explicit MVDockingButton(QWidget *parent = nullptr);

    ~MVDockingButton() override;

private:
    Ui::MVDockingButton *ui;
};


#endif //CHRYSALIS_MVDOCKINGBUTTON_H