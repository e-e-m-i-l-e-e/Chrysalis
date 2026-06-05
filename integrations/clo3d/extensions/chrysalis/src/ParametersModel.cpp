#include "ParametersModel.h"

#include <QMetaType>
Q_DECLARE_METATYPE(Chrysalis::Parameter*)

using namespace UI;

ParametersModel::ParametersModel(Chrysalis::ParametersContainer* parameters)
    : parameters_(parameters) {}

int ParametersModel::rowCount(const QModelIndex& parent) const {
    return parameters_->count();
}

QVariant ParametersModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::UserRole) return {};
    return QVariant::fromValue(parameters_->at(index.row()));
}
