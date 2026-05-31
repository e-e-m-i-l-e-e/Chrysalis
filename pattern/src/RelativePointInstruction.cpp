#include "RelativePointInstruction.h"

RelativePointInstruction::RelativePointInstruction(Space* space,
                                         PatternSpacesArgument* patternSpaces,
                                         Argument<std::string>* pointFrom,
                                         Argument<std::string>* pointTo,
                                         Argument<double>* angle,
                                         Argument<double>* distance)
    : space_(space), patternSpaces_(patternSpaces), pointFrom_(pointFrom), pointTo_(pointTo), angle_(angle),
      distance_(distance) {
    patternSpaces_->addObserver(this);
    pointFrom_->addObserver(this);
    pointTo_->addObserver(this);
    angle_->addObserver(this);
    distance_->addObserver(this);
}

RelativePointInstruction::~RelativePointInstruction() {
    delete pointFrom_;
    delete pointTo_;
    delete angle_;
    delete distance_;
}

void RelativePointInstruction::reset() {
}

void RelativePointInstruction::execute() {
    if (!pointFrom_->hasArgument()) space_->nextPoint(pointTo_->getArgument(), angle_->getArgument(), distance_->getArgument());
    else space_->addPoint(pointFrom_->getArgument(), pointTo_->getArgument(), angle_->getArgument(), distance_->getArgument());
    // boost::optional<std::string> from = pointFrom_->getValue();
    // const std::string to = pointTo_->getValue();
    // for (const auto patternSpace: patternSpaces_->getValue()) {
    //     if (from && !patternSpace->hasPoint(from.value()) || patternSpace->hasPoint(to)) return;
    // }
    // if (from) {
    //     std::unordered_set<Point*> pointsFrom;
    //     for (const auto patternSpace: patternSpaces_->getValue()) {
    //         pointsFrom.insert(patternSpace->getPoint(from.value()));
    //     }
    //     if (pointsFrom.size() > 1) return;
    //     Point* point = space_->addPoint(pointsFrom.begin(), angle_->getValue(), distance_->getValue());
    //     for (const auto patternSpace: patternSpaces_->getValue()) {
    //         patternSpace->addPoint(to, point);
    //     }
    // }

}
