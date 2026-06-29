#ifndef CHRYSALIS_PARAMETERSMODEL_H
#define CHRYSALIS_PARAMETERSMODEL_H

#include <QtQmlIntegration/QtQmlIntegration>

#include "Parameter.h"

namespace Chrysalis {
    class ParametersModel: public QAbstractTableModel {
        Q_OBJECT
        QML_NAMED_ELEMENT(ChrysalisParametersModel)
    public:
        void setParameters(ParametersContainer* parameters);

        [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
        [[nodiscard]] int columnCount(const QModelIndex& parent) const override;

        [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;
        [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;
        bool setData(const QModelIndex& index, const QVariant& value, int role) override;

        [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    private:
        ParametersContainer* parameters_ = nullptr;
    };
}

#endif //CHRYSALIS_PARAMETERSMODEL_H