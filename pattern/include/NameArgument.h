#ifndef CHRYSALIS_NAMEARGUMENT_H
#define CHRYSALIS_NAMEARGUMENT_H
#include "Argument.h"

class NameArgument: public Argument<std::string> {
public:
    explicit NameArgument() = default;
    explicit NameArgument(const std::string& name): Argument(name) {}
};

#endif //CHRYSALIS_NAMEARGUMENT_H