#ifndef CLOEXTENSIONS_MVDOCKWIDGETTITLEBARBASE_H
#define CLOEXTENSIONS_MVDOCKWIDGETTITLEBARBASE_H

#include <QWidget>

class MVDockWidgetTitleBarBase : public QWidget {
    Q_OBJECT

public:
    explicit MVDockWidgetTitleBarBase(QWidget *parent = nullptr);

    ~MVDockWidgetTitleBarBase() override;
};


#endif //CLOEXTENSIONS_MVDOCKWIDGETTITLEBARBASE_H