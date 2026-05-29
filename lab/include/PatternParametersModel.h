#ifndef FASHIONDESIGNAPPS_PATTERNPARAMETERSMODEL_H
#define FASHIONDESIGNAPPS_PATTERNPARAMETERSMODEL_H

#include <QtQmlIntegration/QtQmlIntegration>

#include "ProjectParameters.h"

class PatternParametersModel: public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT
public:
    void setParameters(ProjectParameters* parameters);

    [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
    [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override;
private:
    ProjectParameters* parameters_ = nullptr;
};


#endif //FASHIONDESIGNAPPS_PATTERNPARAMETERSMODEL_H