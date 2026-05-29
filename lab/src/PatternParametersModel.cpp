#include "PatternParametersModel.h"

#include <iostream>

void PatternParametersModel::setParameters(Chrysalis::Parameters* parameters) {
    beginResetModel();
    parameters_ = parameters;
    endResetModel();
}

int PatternParametersModel::rowCount(const QModelIndex& parent) const {
    return parameters_ ? parameters_->count() : 0;
}

int PatternParametersModel::columnCount(const QModelIndex& parent) const {
    return 2;
}

QVariant PatternParametersModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole) return {};
    return index.column() == 0 ? QVariant(QString::fromStdString(parameters_->at(index.row())->getName())) : parameters_->at(index.row())->getValue();
}
