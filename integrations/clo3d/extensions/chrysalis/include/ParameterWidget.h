#ifndef CHRYSALIS_PARAMETERWIDGET_H
#define CHRYSALIS_PARAMETERWIDGET_H

#include <QWidget>
#include <QMetaType>

#include "Parameter.h"

Q_DECLARE_METATYPE(Chrysalis::Parameter*)

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

        void setParameter(Chrysalis::Parameter* parameter);
    private:
        Chrysalis::Parameter* parameter_ = nullptr;
        Ui::ParameterWidget* ui;
    };
} // UI

#endif //CHRYSALIS_PARAMETERWIDGET_H