#include "../include/data/ArgumentEvaluationData.h"

using namespace Chrysalis;

ArgumentEvaluationData::ArgumentEvaluationData(BaseArgument<double>* expression, std::string&& expressionText, double expected)
    : expression_(expression), expressionText_(std::move(expressionText)), expected_(expected) {}

BaseArgument<double>* ArgumentEvaluationData::expression() const {
    return expression_;
}

const std::string& ArgumentEvaluationData::expressionText() const {
    return expressionText_;
}

double ArgumentEvaluationData::expected() const {
    return expected_;
}
