#ifndef CHRYSALIS_BASECOMMAND_H
#define CHRYSALIS_BASECOMMAND_H

#include "CLO3DExtensionExport.h"

#include "BaseCommandArguments.h"

namespace CLO3D {
    class CLO3D_EXTENSION BaseCommand {
    protected:
        explicit BaseCommand(BaseCommandArguments* arguments);
    public:
        virtual ~BaseCommand();

        virtual void run() = 0;
    protected:
        /// @uml{composition}
        BaseCommandArguments* arguments_;
    };
}

#endif //CHRYSALIS_BASECOMMAND_H