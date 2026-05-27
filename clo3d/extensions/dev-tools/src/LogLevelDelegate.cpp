#include "LogLevelDelegate.h"

#include <QTimer>
#include <QComboBox>
#include <QApplication>

LogLevelDelegate::LogLevelDelegate(QWidget* parent): QStyledItemDelegate(parent) {}

QWidget* LogLevelDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& index) const {
    auto* combo = new QComboBox(parent);
    combo->addItems({"trace", "debug", "info", "warning", "error", "fatal"});
    QTimer::singleShot(0, combo, &QComboBox::showPopup);
    return combo;
}

void LogLevelDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
    static_cast<QComboBox*>(editor)->setCurrentText(index.data(Qt::EditRole).toString());
}

void LogLevelDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
    // model->setData(index, static_cast<QComboBox*>(editor)->currentText(), Qt::EditRole);
}
