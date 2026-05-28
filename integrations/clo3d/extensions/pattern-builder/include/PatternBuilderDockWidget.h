#ifndef CLOEXTENSIONS_PATTERNBUILDERDOCKWIDGET_H
#define CLOEXTENSIONS_PATTERNBUILDERDOCKWIDGET_H

#include <QDockWidget>

QT_BEGIN_NAMESPACE

namespace Ui {
    class PatternBuilderDockWidget;
}

QT_END_NAMESPACE

class PatternBuilderDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit PatternBuilderDockWidget(QWidget *parent = nullptr);

    ~PatternBuilderDockWidget() override;

private:
    Ui::PatternBuilderDockWidget *ui;
};


#endif //CLOEXTENSIONS_PATTERNBUILDERDOCKWIDGET_H