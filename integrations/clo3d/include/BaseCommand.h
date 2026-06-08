#ifndef CHRYSALIS_BASECOMMAND_H
#define CHRYSALIS_BASECOMMAND_H

#include "BaseCommandArguments.h"

class BaseCommand {
protected:
    explicit BaseCommand(BaseCommandArguments* arguments);
public:
    virtual ~BaseCommand();

    virtual void run() = 0;
protected:
    /// @uml[composition]
    BaseCommandArguments* arguments_;
};

#endif //CHRYSALIS_BASECOMMAND_H