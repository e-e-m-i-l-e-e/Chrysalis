#include "PatternParametersModel.h"

#include <iostream>

void PatternParametersModel::setParameters(ProjectParameters* parameters) {
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
    return {"TEST"};
}
