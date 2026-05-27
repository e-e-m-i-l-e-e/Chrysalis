#include "LoggerRegistryModel.h"

#include "LoggerRegistry.h"

LoggerRegistryModel::LoggerRegistryModel(QObject* parent, LoggerRegistry& registry)
    : QAbstractTableModel(parent), registry_(registry) {}

Qt::ItemFlags LoggerRegistryModel::flags(const QModelIndex& index) const {
    auto flags = QAbstractTableModel::flags(index);
    if (index.column() == 1) flags |= Qt::ItemIsEditable;
    return flags;
}

int LoggerRegistryModel::rowCount(const QModelIndex& parent) const {
    return static_cast<int>(registry_.getLoggers().size());
}

int LoggerRegistryModel::columnCount(const QModelIndex& parent) const {
    return 2;
}

QVariant LoggerRegistryModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
    const auto loggers = registry_.getLoggers();
    auto currentLoggerIt = loggers.begin();
    std::advance(currentLoggerIt, index.row());
    return index.column() == 0 ? currentLoggerIt->first : currentLoggerIt->second->getLevel();
}

QVariant LoggerRegistryModel::headerData(const int section, const Qt::Orientation orientation, const int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    return section == 0 ? "Name" : "Level";
}