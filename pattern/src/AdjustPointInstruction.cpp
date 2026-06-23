#include "instructions/AdjustPointInstruction.h"

Chrysalis::AdjustPointInstruction::AdjustPointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                                          const name* pointName, const name* pointName1,
                                                          const num* length1, const name* pointName2,
                                                          const num* length2)
    : BasePatternInstruction(space, patterns), pointName_(pointName), pointName1_(pointName1), length1_(length1),
      pointName2_(pointName2), length2_(length2) {}

Chrysalis::AdjustPointInstruction::~AdjustPointInstruction() {
    delete pointName_;
    delete pointName1_;
    delete length1_;
    delete pointName2_;
    delete length2_;
}

bool Chrysalis::AdjustPointInstruction::isValid() {
    return pointName_->hasArgument() && allPatternsSharePoint(pointName_->getArgument()) &&
        pointName1_->hasArgument() && allPatternsSharePoint(pointName1_->getArgument()) && length1_->hasArgument() &&
        pointName2_->hasArgument() && allPatternsSharePoint(pointName2_->getArgument()) && length2_->hasArgument();
}

void Chrysalis::AdjustPointInstruction::execute() {
    const auto point = anyPattern()->getPoint(pointName_->getArgument());
    space().movePoint(point, ProjectSpace::circlesIntersection(
        *point,
        *anyPattern()->getPoint(pointName1_->getArgument()), length1_->getArgument(),
        *anyPattern()->getPoint(pointName2_->getArgument()), length2_->getArgument()
    ));
}
