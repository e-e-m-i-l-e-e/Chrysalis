#ifndef FASHIONDESIGNAPPS_LOGGERTEXTEDIT_H
#define FASHIONDESIGNAPPS_LOGGERTEXTEDIT_H

#include <spdlog/sinks/qt_sinks.h>

#include <QTextEdit>

#include "Logger.h"

class LoggerTextEditSink: public QTextEdit {
    Q_OBJECT
public:
    explicit LoggerTextEditSink(QWidget* parent);

    void attach(Logger* logger) const;
public slots:
    void format(const QString& text);
protected:
    void showEvent(QShowEvent*) override;
private:
    static constexpr auto FORMAT_METHOD = "format";
    std::shared_ptr<spdlog::sinks::qt_sink_mt> sink_;

    QTextCursor cursor_;
    QTextCharFormat defaultFormat_;
    QTextCharFormat coloredFormat_;
};


#endif //FASHIONDESIGNAPPS_LOGGERTEXTEDIT_H