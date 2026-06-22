#include "arguments/VectorFunction.h"

using namespace Chrysalis;

boost::optional<double> VectorFunction::Length::evaluate(const name* pointFrom, const pattern* patternFrom,
                                                          const name* pointTo, const pattern* patternTo) const {
    return VectorFunction::evaluate(pointFrom, patternFrom, pointTo, patternTo, ProjectSpace::length);
}

boost::optional<double> VectorFunction::Angle::evaluate(const name* pointFrom, const pattern* patternFrom,
                                                         const name* pointTo, const pattern* patternTo) const {
    return VectorFunction::evaluate(pointFrom, patternFrom, pointTo, patternTo, static_cast<double(*)(const CGAL::Point&, const CGAL::Point&)>(ProjectSpace::angle));
}

boost::optional<double> VectorFunction::evaluate(const name* pointFrom, const pattern* patternFrom,
                                                            const name* pointTo, const pattern* patternTo,
                                                            const std::function<double(const Point& from, const Point& to)>& evaluator) {
    if (!pointFrom->hasArgument() || !patternFrom->hasArgument() || !pointTo->hasArgument() || !patternTo->hasArgument() ||
        !patternFrom->getArgument()->hasPoint(pointFrom->getArgument()) || !patternTo->getArgument()->hasPoint(pointTo->getArgument())) return boost::none;
    return evaluator(*patternFrom->getArgument()->getPoint(pointFrom->getArgument()), *patternTo->getArgument()->getPoint(pointTo->getArgument()));
}