#ifndef FASHIONDESIGNAPPS_PATTERNPARAMETERSMODEL_H
#define FASHIONDESIGNAPPS_PATTERNPARAMETERSMODEL_H

#include <QAbstractListModel>

class PatternParametersModel: public QAbstractListModel {
    Q_OBJECT
public:
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
};


#endif //FASHIONDESIGNAPPS_PATTERNPARAMETERSMODEL_H