#include "LoggerTextEditSink.h"

#include <QScrollBar>
#include <QRegularExpression>

#include "Logger.h"
#include "LoggerFormatter.h"
#include "formatters/ColoredLevelFlagFormatter.h"
#include "formatters/ColoredNameFlagFormatter.h"

using namespace UI;

LoggerTextEditSink::LoggerTextEditSink(QWidget* parent)
    : QTextEdit(parent), sink_(std::make_shared<spdlog::sinks::qt_sink_mt>(this, FORMAT_METHOD)), cursor_(document()) {
    setReadOnly(true);

    LoggerFormatter<ColoredNameFlagFormatter, ColoredLevelFlagFormatter>::apply(sink_);

    static constexpr auto FONT_SIZE  = 7;
    static constexpr auto FONT_FAMILY = "Courier New";

    QFont font(FONT_FAMILY);
    font.setStyleHint(QFont::Monospace);
    font.setPointSize(FONT_SIZE);

    defaultFormat_.setFont(font);
    coloredFormat_.setFont(font);
}

void LoggerTextEditSink::attach(Logger* logger) const {
    logger->addSink(sink_);
}

void LoggerTextEditSink::format(const QString& text) {
    static constexpr auto ANSI_PATTERN = R"(\x1B\[(\d+(?:;\d+)*)m)";
    static const QRegularExpression ansiRegex(ANSI_PATTERN);
    static const QList palette = {
        QColor("#808080"), // 0: black/bright black (trace)
        QColor("#f44747"), // 1: red
        QColor("#4ec994"), // 2: green
        QColor("#ce9178"), // 3: yellow
        QColor("#569cd6"), // 4: blue
        QColor("#c678dd"), // 5: magenta
        QColor("#56b6c2"), // 6: cyan
        QColor("#ffffff"), // 7: white
    };
    static const auto colorFor = [](const int n) -> QColor {
        if (n >= 30 && n <= 37) return palette[n - 30];
        if (n >= 90 && n <= 97) return palette[n - 90];
        return {};
    };

    QList<QColor> colors;
    auto it = ansiRegex.globalMatch(text);
    while (it.hasNext()) {
        for (const auto match = it.next(); const QString& code: match.captured(1).split(';')) {
            const int n = code.toInt();
            if (const QColor c = colorFor(n); c.isValid()) colors.append(c);
        }
    }

    const QString clean = QString(text).remove(ansiRegex);

    const int levelStart = clean.indexOf('[');
    const int levelEnd = clean.indexOf(']', levelStart + 1);
    const int nameStart = clean.indexOf('[', levelEnd + 1);
    const int nameEnd = clean.indexOf(']', nameStart + 1);

    cursor_.insertText(clean.mid(0, levelStart), defaultFormat_);

    coloredFormat_.setForeground(colors[0]);
    cursor_.insertText(clean.mid(levelStart, levelEnd - levelStart + 1), coloredFormat_);

    cursor_.insertText(clean.mid(levelEnd + 1, nameStart - levelEnd - 1), defaultFormat_);

    coloredFormat_.setForeground(colors[1]);
    cursor_.insertText(clean.mid(nameStart, nameEnd - nameStart + 1), coloredFormat_);

    cursor_.insertText(clean.mid(nameEnd + 1), defaultFormat_);
    cursor_.insertBlock();
}

void LoggerTextEditSink::showEvent(QShowEvent* show_event) {
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
    QTextEdit::showEvent(show_event);
}
