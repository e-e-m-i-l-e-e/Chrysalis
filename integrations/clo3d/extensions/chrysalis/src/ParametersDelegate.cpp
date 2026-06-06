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

void ParametersDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    static int height = editor->sizeHint().height();
    const int y = option.rect.y() + (option.rect.height() - height) / 2;
    editor->setGeometry(option.rect.x(), y, option.rect.width(), height);
}

QWidget* ParametersDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    return new ParameterWidget(parent);
}

void ParametersDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
    qobject_cast<ParameterWidget*>(editor)->setParameter(index.data(Qt::UserRole).value<Chrysalis::Parameter*>());
}