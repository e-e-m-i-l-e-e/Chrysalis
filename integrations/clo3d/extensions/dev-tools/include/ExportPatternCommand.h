#ifndef CHRYSALIS_EXPORTPATTERNCOMMAND_H
#define CHRYSALIS_EXPORTPATTERNCOMMAND_H

#include "BaseCommand.h"
#include "ExportPatternCommandArguments.h"

namespace CLO3D {
    class ExportPatternCommand: public BaseCommand {
    public:
        explicit ExportPatternCommand(ExportPatternCommandArguments* arguments);

        void run() override;
    };
}

#endif //CHRYSALIS_EXPORTPATTERNCOMMAND_H