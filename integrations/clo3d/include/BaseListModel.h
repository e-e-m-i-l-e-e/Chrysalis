#ifndef CHRYSALIS_BASEMODEL_H
#define CHRYSALIS_BASEMODEL_H

#include <QMetaType>
#include <QAbstractListModel>

#include "Parameter.h"

Q_DECLARE_METATYPE(Chrysalis::Parameter*)

namespace UI {
    template<typename T>
    class BaseModel: public QAbstractListModel {
    protected:
        explicit BaseModel(T* data): data_(data) {}
    public:
        int rowCount(const QModelIndex& parent) const override {
            return data_->count();
        }
        QVariant data(const QModelIndex& index, const int role) const override {
            if (role != Qt::UserRole) return {};
            return QVariant::fromValue((*data_)[index.row()]);
        }
    private:
        T* data_;
    };
}

#endif //CHRYSALIS_BASEMODEL_H