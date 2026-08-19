#include "LoggerRegistryModel.h"

#include "LoggerRegistry.h"

using namespace CLO3D::UI;

LoggerRegistryModel::LoggerRegistryModel(QObject* parent, Logging::LoggerRegistry& registry)
    : QAbstractTableModel(parent), registry_(registry) {}

Qt::ItemFlags LoggerRegistryModel::flags(const QModelIndex& index) const {
    auto flags = QAbstractTableModel::flags(index);
    if (index.column() == 1) flags |= Qt::ItemIsEditable;
    return flags;
}

int LoggerRegistryModel::rowCount(const QModelIndex& parent) const {
    return static_cast<int>(registry_.size());
}

int LoggerRegistryModel::columnCount(const QModelIndex& parent) const {
    return 2;
}

QVariant LoggerRegistryModel::data(const QModelIndex& index, const int role) const {
    if (role != Qt::DisplayRole) return {};
    const auto logger = registry_.at(index.row());
    return index.column() == 0 ? QVariant(logger->getName()) : static_cast<int>(logger->getLevel());
}

QVariant LoggerRegistryModel::headerData(const int section, const Qt::Orientation orientation, const int role) const {
    constexpr static auto NAME_COLUMN = "Name";
    constexpr static auto LEVEL_COLUMN = "Level";
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    return section == 0 ?  NAME_COLUMN : LEVEL_COLUMN;
}