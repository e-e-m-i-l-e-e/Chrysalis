#ifndef FASHIONDESIGNAPPS_LOGLEVELDELEGATE_H
#define FASHIONDESIGNAPPS_LOGLEVELDELEGATE_H

#include <QComboBox>
#include <QStyledItemDelegate>

#include "LoggerRegistryModel.h"

class LogLevelDelegate: public QStyledItemDelegate {
public:
    explicit LogLevelDelegate(LoggerRegistryModel* model);

    int getLevel(int row) const;
    void setLevel(int row, int value) const;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
private:
    std::vector<QComboBox*> editors_;
};

#endif //FASHIONDESIGNAPPS_LOGLEVELDELEGATE_H