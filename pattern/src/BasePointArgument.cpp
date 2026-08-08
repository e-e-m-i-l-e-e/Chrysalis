#include "arguments/BasePointArgument.h"

using namespace Chrysalis;

bool BasePointArgument::isValid() const {
    return true;
}

BasePointArgument::operator CG::Point() const {
    return *get();
}