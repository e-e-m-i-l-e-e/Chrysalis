#ifndef CHRYSALIS_PARAMETERWIDGET_H
#define CHRYSALIS_PARAMETERWIDGET_H

#include <QWidget>

#include "Parameter.h"

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class ParameterWidget;
    }
    QT_END_NAMESPACE

    class ParameterWidget: public QWidget {
        Q_OBJECT
    public:
        explicit ParameterWidget(QWidget* parent = nullptr);
        ~ParameterWidget() override;

        void set(Chrysalis::Parameter* parameter);
    private:
        Chrysalis::Parameter* parameter_ = nullptr;
        Ui::ParameterWidget* ui;
    };
} // UI

#endif //CHRYSALIS_PARAMETERWIDGET_H