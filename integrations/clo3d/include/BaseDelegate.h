#ifndef CHRYSALIS_BASEDELEGATE_H
#define CHRYSALIS_BASEDELEGATE_H

#include <QStyledItemDelegate>

namespace CLO3D::UI {
    template<typename W, typename C>
    requires std::is_base_of_v<QWidget, W>
    class BaseDelegate: public QStyledItemDelegate {
    public:
        explicit BaseDelegate(QObject* parent): QStyledItemDelegate(parent) {}

        QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override {
            static int height = W().height();
            return {0, height};
        }
        void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
            static int height = editor->sizeHint().height();
            const int y = option.rect.y() + (option.rect.height() - height) / 2;
            editor->setGeometry(option.rect.x(), y, option.rect.width(), height);
        }

        void setEditorData(QWidget* editor, const QModelIndex& index) const override {
            qobject_cast<W*>(editor)->set(index.data(Qt::UserRole).value<C*>());
        }
        QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
            return new W(parent);
        }
    };
}

#endif //CHRYSALIS_BASEDELEGATE_H