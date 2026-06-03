#ifndef CHRYSALIS_PARAMETERSELEMENT_H
#define CHRYSALIS_PARAMETERSELEMENT_H

#include <QQuickItem>

#include "ParametersModel.h"

namespace Chrysalis {
    class ParametersElement: public QQuickItem {
        Q_OBJECT
        QML_NAMED_ELEMENT(ChrysalisParameters)

        Q_PROPERTY(ParametersModel* model READ getModel WRITE setModel NOTIFY modelChanged)
    public:
        void setParameters(ParametersContainer* parameters);

        [[nodiscard]] ParametersModel* getModel() const;
        void setModel(ParametersModel* model);

        signals:
        void modelChanged();
    private:
        ParametersModel* model_ = nullptr;
        ParametersContainer* parameters_ = nullptr;
    };
}

#endif //CHRYSALIS_PARAMETERSELEMENT_H