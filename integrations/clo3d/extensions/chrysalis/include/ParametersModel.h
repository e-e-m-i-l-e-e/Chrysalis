#ifndef CHRYSALIS_PARAMETERMODEL_H
#define CHRYSALIS_PARAMETERMODEL_H

#include <QAbstractListModel>

#include "ParametersContainer.h"

namespace UI {
    class ParametersModel: public QAbstractListModel {
    public:
        explicit ParametersModel(Chrysalis::ParametersContainer* parameters);

        int rowCount(const QModelIndex& parent) const override;
        QVariant data(const QModelIndex& index, int role) const override;
    private:
        Chrysalis::ParametersContainer* parameters_;
    };
}

#endif //CHRYSALIS_PARAMETERMODEL_H