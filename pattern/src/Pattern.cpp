#include "Pattern.h"

using namespace Chrysalis;

Pattern::Pattern(const std::string& name, PatternSpace* space)
    : name_(name), space_(space) {}

Pattern::~Pattern() {
    delete space_;
}
