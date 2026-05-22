#include "Argument.h"

Argument::Argument(const double value): value_(value) {}

double Argument::getValue() const{
    return value_;
}
