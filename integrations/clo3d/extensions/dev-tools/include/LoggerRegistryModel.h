#ifndef CHRYSALIS_LOGGERREGISTRYMODEL_H
#define CHRYSALIS_LOGGERREGISTRYMODEL_H

#include <QAbstractTableModel>

#include "Logger.h"
#include "LoggerRegistry.h"

namespace CLO3D::UI {
    class LoggerRegistryModel: public QAbstractTableModel {
    public:
        explicit LoggerRegistryModel(QObject* parent, Logging::LoggerRegistry& registry);

        [[nodiscard]] Qt::ItemFlags flags(const QModelIndex& index) const override;
        [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
        [[nodiscard]] int columnCount(const QModelIndex& parent) const override;
        [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;
        [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    private:
        Logging::LoggerRegistry& registry_;
    };

}

#endif //CHRYSALIS_LOGGERREGISTRYMODEL_H