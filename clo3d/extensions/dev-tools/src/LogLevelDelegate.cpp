#include "LogLevelDelegate.h"

#include <QTimer>
#include <QComboBox>

LogLevelDelegate::LogLevelDelegate(LoggerRegistryModel* model): QStyledItemDelegate(model), editors_(model->rowCount({})) {
    static const auto prepareLevels = [] {
        QStringList levels;
        for (int i = 0; i < spdlog::level::n_levels; i++) {
            levels << QString(spdlog::level::to_string_view(static_cast<spdlog::level::level_enum>(i)).data()).toUpper();
        }
        return levels;
    };
    static const QStringList LOG_LEVELS = prepareLevels();

    for (auto& editor: editors_) {
        editor = new QComboBox();
        editor->addItems(LOG_LEVELS);
        editor->setFocusPolicy(Qt::NoFocus);
    }
}

int LogLevelDelegate::getLevel(const int row) const {
    return editors_[row]->currentIndex();
}

void LogLevelDelegate::setLevel(const int row, const int value) const {
    editors_[row]->setCurrentIndex(value);
}

QWidget* LogLevelDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& index) const {
    auto& editor = editors_[index.row()];
    editor->setParent(parent);
    return editor;
}