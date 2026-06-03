#ifndef CHRYSALIS_BASEINSTRUCTION_H
#define CHRYSALIS_BASEINSTRUCTION_H

namespace Chrysalis {
    class BaseInstruction {
    protected:
        explicit BaseInstruction() = default;
        virtual ~BaseInstruction() = default;
    public:
        virtual void execute() = 0;
    };
}

#endif //CHRYSALIS_BASEINSTRUCTION_H