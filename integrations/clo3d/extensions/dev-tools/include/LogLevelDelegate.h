#ifndef CHRYSALIS_LOGLEVELDELEGATE_H
#define CHRYSALIS_LOGLEVELDELEGATE_H

#include <QComboBox>
#include <QStyledItemDelegate>

#include "LoggerRegistryModel.h"

namespace UI {
    class LogLevelDelegate: public QStyledItemDelegate {
    public:
        explicit LogLevelDelegate(LoggerRegistryModel* model);

        void setLevel(int row, int value) const;
        [[nodiscard]] int getLevel(int row) const;

        QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    private:
        std::vector<QComboBox*> editors_;
    };
}

#endif //CHRYSALIS_LOGLEVELDELEGATE_H