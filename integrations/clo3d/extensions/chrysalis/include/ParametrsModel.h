#ifndef CHRYSALIS_PARAMETRSMODEL_H
#define CHRYSALIS_PARAMETRSMODEL_H

#include "ParameterWidget.h"
#include "BaseListModel.h"

namespace CLO3D::UI {
    class ParametersModel: public BaseModel<Chrysalis::ParametersContainer> {
    public:
        explicit ParametersModel(Chrysalis::ParametersContainer* parameters): BaseModel(parameters) {}
    };
}

#endif //CHRYSALIS_PARAMETRSMODEL_H
