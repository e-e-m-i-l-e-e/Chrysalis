#include "arguments/VectorFunctionArgument.h"

boost::optional<double> Chrysalis::VectorFunction::length(const name* pointFrom, const pattern* patternFrom,
                                                          const name* pointTo, const pattern* patternTo) {
    return evaluate(pointFrom, patternFrom, pointTo, patternTo, ProjectSpace::length);
}

boost::optional<double> Chrysalis::VectorFunction::angle(const name* pointFrom, const pattern* patternFrom,
                                                         const name* pointTo, const pattern* patternTo) {
    return evaluate(pointFrom, patternFrom, pointTo, patternTo, static_cast<double(*)(const CGAL::Point&, const CGAL::Point&)>(ProjectSpace::angle));
}

boost::optional<double> Chrysalis::VectorFunction::evaluate(const name* pointFrom, const pattern* patternFrom,
                                                            const name* pointTo, const pattern* patternTo,
                                                            const std::function<double(const Point& from, const Point& to)>& evaluator) {
    if (!pointFrom->hasArgument() || !patternFrom->hasArgument() || !pointTo->hasArgument() || !patternTo->hasArgument()) return boost::none;
    return evaluator(*patternFrom->getArgument()->getPoint(pointFrom->getArgument()), *patternTo->getArgument()->getPoint(pointTo->getArgument()));
}

Chrysalis::VectorFunctionArgument::VectorFunctionArgument(const name* pointFrom, const pattern* patternFrom,
                                                          const name* pointTo, const pattern* patternTo,
                                                          boost::optional<double> (VectorFunction::*function)(
                                                              const name* pointFrom, const pattern* patternFrom,
                                                              const name* pointTo, const pattern* patternTo))
    : NumberArgument([&] {
        return (evaluator.*function)(pointFrom, patternFrom, pointTo, patternTo);
    }()), pointFrom_(pointFrom), patternFrom_(patternFrom), pointTo_(pointTo), patternTo_(patternTo), function_(function) {}

Chrysalis::VectorFunctionArgument::~VectorFunctionArgument() {
    delete pointFrom_;
    delete patternFrom_;
    delete pointTo_;
    delete patternTo_;
}
