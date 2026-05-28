#ifndef CHRYSALIS_MVDOCKWIDGETTITLEBARBASE_H
#define CHRYSALIS_MVDOCKWIDGETTITLEBARBASE_H

#include <QWidget>

class MVDockWidgetTitleBarBase : public QWidget {
    Q_OBJECT

public:
    explicit MVDockWidgetTitleBarBase(QWidget *parent = nullptr): QWidget(parent) {};

    ~MVDockWidgetTitleBarBase() override {};
};


#endif //CHRYSALIS_MVDOCKWIDGETTITLEBARBASE_H