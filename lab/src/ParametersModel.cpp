#include "ParametersModel.h"

#include <iostream>

using namespace Chrysalis;

void ParametersModel::setParameters(ParametersContainer* parameters) {
    beginResetModel();
    parameters_ = parameters;
    endResetModel();
}

int ParametersModel::rowCount(const QModelIndex& parent) const {
    return parameters_ ? parameters_->count() : 0;
}

int ParametersModel::columnCount(const QModelIndex& parent) const {
    return 4;
}

Qt::ItemFlags ParametersModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    flags |= Qt::ItemIsEditable;
    return flags;
}

QVariant ParametersModel::data(const QModelIndex& index, const int role) const {
    if (!parameters_ || role != Qt::DisplayRole) return {};
    const auto parameter = (*parameters_)[index.row()];
    if (index.column() == 0) return parameter->getName().data();
    if (index.column() == 1) return parameter->hasValue() ? QVariant(parameter->getValue()) : "";
    if (index.column() == 2) return parameter->hasDefaultValue() ? QVariant(parameter->getDefaultValue()) : "";
    if (index.column() == 3) return parameter->hasAlias() ? parameter->getAlias().data() : "";
    return {};
}

QVariant ParametersModel::headerData(const int section, const Qt::Orientation orientation, const int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "Name";
            case 1: return "Value";
            case 2: return "Default Value";
            case 3: return "Alias";
            default: return {};
        }
    }
    return {};
}

bool ParametersModel::setData(const QModelIndex& index, const QVariant& value, const int role) {
    if (role == Qt::DisplayRole) {
        if (index.column() == 1) {
            (*parameters_)[index.row()]->setValue(value.toDouble());
            return true;
        }
        return false;
    }
    return false;
}
