#include "arguments/VectorFunction.h"

using namespace Chrysalis;

double VectorFunction::Length::evaluate(const args::point* from, const args::point* to) const {
    return VectorFunction::evaluate(from, to, ProjectSpace::length);
}

double VectorFunction::Angle::evaluate(const args::point* from, const args::point* to) const {
    return VectorFunction::evaluate(from, to, static_cast<double(*)(const CGAL::Point&, const CGAL::Point&)>(ProjectSpace::angle));
}

double VectorFunction::evaluate(const args::point* from, const args::point* to,
                                const std::function<double(const Point& from, const Point& to)>& evaluator) {
    return evaluator(*from->get(), *to->get());
}