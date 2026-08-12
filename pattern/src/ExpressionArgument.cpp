#include "arguments/ExpressionArgument.h"

using namespace Chrysalis;

ExpressionArgument::ExpressionArgument(const ExpressionsContainer* expressions, const args::name* name)
    : expressions_(expressions), name_(name) {}

ExpressionArgument::~ExpressionArgument() {
    delete name_;
}

std::expected<double, Error> ExpressionArgument::calculate() const {
    return name_->get().and_then([this](const std::string& name) -> std::expected<double, Error> {
        if (!expressions_->has(name)) return std::unexpected(Error{"Requested expression doesn't exist: \"" + name + "\""});
        return expressions_->get(name)->get();
    });
}
