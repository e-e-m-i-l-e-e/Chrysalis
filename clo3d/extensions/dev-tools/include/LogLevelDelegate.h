#ifndef FASHIONDESIGNAPPS_LOGLEVELDELEGATE_H
#define FASHIONDESIGNAPPS_LOGLEVELDELEGATE_H

#include <QStyledItemDelegate>

class LogLevelDelegate: public QStyledItemDelegate {
public:
    explicit LogLevelDelegate(QWidget* parent);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};

#endif //FASHIONDESIGNAPPS_LOGLEVELDELEGATE_H