#ifndef CHRYSALIS_VECTORFUNCTIONS_H
#define CHRYSALIS_VECTORFUNCTIONS_H

#include "ProjectSpace.h"
#include "NumberArgument.h"

namespace Chrysalis {
    class VectorFunctionArgument: public NumberArgument {
    public:
        struct Use {
            static double ANGLE(const VectorFunctionArgument* function);
            static double LENGTH(const VectorFunctionArgument* function);
        };
        explicit VectorFunctionArgument(ProjectSpace* space, std::string  from, std::string  to, double(*function)(const VectorFunctionArgument*));
    private:
        ProjectSpace* space;

        std::string from;
        std::string to;

        double(*function)(const VectorFunctionArgument*);
    };
}

#endif //CHRYSALIS_VECTORFUNCTIONS_H