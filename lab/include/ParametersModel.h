#ifndef CHRYSALIS_PARAMETERSMODEL_H
#define CHRYSALIS_PARAMETERSMODEL_H

#include <QtQmlIntegration/QtQmlIntegration>

#include "Parameters.h"

namespace Chrysalis {
    class ParametersModel: public QAbstractTableModel {
        Q_OBJECT
        QML_NAMED_ELEMENT(ChrysalisParametersModel)
    public:
        void setParameters(Parameters* parameters);

        int rowCount(const QModelIndex& parent) const override;
        int columnCount(const QModelIndex& parent) const override;
        QVariant data(const QModelIndex& index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    private:
        Parameters* parameters_ = nullptr;
    };
}

#endif //CHRYSALIS_PARAMETERSMODEL_H