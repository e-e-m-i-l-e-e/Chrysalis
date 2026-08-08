#include "Transformation.h"

using namespace Chrysalis;

Transformation::Transformation(const Point* origin, CG::Vector translation, double angle)
    : origin_(origin), translation_(std::move(translation)), angle_(std::move(angle)) {}

CG::Point Transformation::apply(CG::Point point) const {
    if (!origin_) return point;
    const CG::Transformation translation(CGAL::TRANSLATION, translation_);

    const CG::Vector to_origin   = CGAL::ORIGIN - static_cast<CG::Point>(*origin_);
    const CG::Vector back_again  = static_cast<CG::Point>(*origin_) - CGAL::ORIGIN;

    const auto rotation =
        CG::Transformation(CGAL::TRANSLATION, back_again) *
        CG::Transformation(CGAL::ROTATION, std::sin(CG::radians(angle_)), std::cos(CG::radians(angle_))) *
        CG::Transformation(CGAL::TRANSLATION, to_origin);

    return translation(rotation(point));
}
