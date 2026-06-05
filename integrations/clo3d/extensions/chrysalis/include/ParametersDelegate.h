#ifndef CHRYSALIS_PARAMETERDELEGATE_H
#define CHRYSALIS_PARAMETERDELEGATE_H

#include <QStyledItemDelegate>

namespace UI {
    class ParametersDelegate: public QStyledItemDelegate {
    public:
        explicit ParametersDelegate(QObject *parent);

        QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

        void setEditorData(QWidget* editor, const QModelIndex& index) const override;
        QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    };
}

#endif //CHRYSALIS_PARAMETERDELEGATE_H