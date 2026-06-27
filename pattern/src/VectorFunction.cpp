#include "arguments/VectorFunction.h"

using namespace Chrysalis;

double VectorFunction::Length::evaluate(const args::name* pointFrom, const pattern* patternFrom,
                                        const args::name* pointTo, const pattern* patternTo) const {
    return VectorFunction::evaluate(pointFrom, patternFrom, pointTo, patternTo, ProjectSpace::length);
}

double VectorFunction::Angle::evaluate(const args::name* pointFrom, const pattern* patternFrom,
                                       const args::name* pointTo, const pattern* patternTo) const {
    return VectorFunction::evaluate(pointFrom, patternFrom, pointTo, patternTo, static_cast<double(*)(const CGAL::Point&, const CGAL::Point&)>(ProjectSpace::angle));
}

double VectorFunction::evaluate(const args::name* pointFrom, const pattern* patternFrom,
                                const args::name* pointTo, const pattern* patternTo,
                                const std::function<double(const Point& from, const Point& to)>& evaluator) {
    return evaluator(*patternFrom->get()->getPoint(pointFrom->get()), *patternTo->get()->getPoint(pointTo->get()));
}