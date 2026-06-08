#ifndef CHRYSALIS_BASECOMMANDARGUMENTS_H
#define CHRYSALIS_BASECOMMANDARGUMENTS_H

#include <QSettings>

class BaseCommandArguments {
protected:
    explicit BaseCommandArguments(QSettings* settings);
public:
    virtual ~BaseCommandArguments() = default;

    void readSettings();
    void writeSettings();

    virtual QString getName() = 0;
protected:
    virtual void read() = 0;
    virtual void write() = 0;

    QSettings* settings_;
};

#endif //CHRYSALIS_BASECOMMANDARGUMENTS_H