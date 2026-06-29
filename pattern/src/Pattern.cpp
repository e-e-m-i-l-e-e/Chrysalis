#include "Pattern.h"

using namespace Chrysalis;

Pattern::Pattern(const std::string& name, PatternSpace* space)
    : BaseNamedElement(name), space_(space) {}

Pattern* Pattern::create(const std::string& name) {
    return new Pattern(name, new PatternSpace(new OutlineContainer()));
}

Pattern::~Pattern() {
    delete space_;
}

PatternSpace* Pattern::getSpace() const {
    return space_;
}
