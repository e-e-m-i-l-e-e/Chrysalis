#ifndef CHRYSALIS_PARAMETERDELEGATE_H
#define CHRYSALIS_PARAMETERDELEGATE_H

#include "BaseDelegate.h"
#include "ParameterWidget.h"

namespace UI {
    class ParameterDelegate: public BaseDelegate<ParameterWidget, Chrysalis::Parameter> {
    public:
        explicit ParameterDelegate(QObject* parent): BaseDelegate(parent) {}
    };
}
#endif //CHRYSALIS_PARAMETERDELEGATE_H
