#ifndef CHRYSALIS_TESTWIDGET_ALLTYPES_H
#define CHRYSALIS_TESTWIDGET_ALLTYPES_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class TestWidget_AllTypes;
}
QT_END_NAMESPACE

class TestWidget_AllTypes : public QWidget {
    Q_OBJECT
public:
    explicit TestWidget_AllTypes(QWidget* parent = nullptr);
    ~TestWidget_AllTypes() override;
private:
    Ui::TestWidget_AllTypes* ui;
};

#endif // CHRYSALIS_TESTWIDGET_ALLTYPES_H
