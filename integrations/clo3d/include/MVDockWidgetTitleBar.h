#ifndef CHRYSALIS_MVDOCKWIDGETTITLEBAR_H
#define CHRYSALIS_MVDOCKWIDGETTITLEBAR_H

#include "MVDockWidgetTitleBarBase.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class MVDockWidgetTitleBar;
}

QT_END_NAMESPACE

class MVDockWidgetTitleBar : public MVDockWidgetTitleBarBase {
    Q_OBJECT

public:
    explicit MVDockWidgetTitleBar(QWidget *parent = nullptr);

    ~MVDockWidgetTitleBar() override;

private:
    Ui::MVDockWidgetTitleBar *ui;
};


#endif //CHRYSALIS_MVDOCKWIDGETTITLEBAR_H