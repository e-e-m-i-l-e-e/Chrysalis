#include "ParametersDelegate.h"
#include <ui_ParameterWidget.h>

#include "ParameterWidget.h"

#include <iostream>

using namespace UI;

ParametersDelegate::ParametersDelegate(QObject *parent): QStyledItemDelegate(parent) {}

QSize ParametersDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
    static int height = ParameterWidget().height();
    return {0, height};
}

QWidget* ParametersDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    return new ParameterWidget(parent);
}

void ParametersDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
    qobject_cast<ParameterWidget*>(editor)->setParameter(index.data(Qt::UserRole).value<Chrysalis::Parameter*>());
}