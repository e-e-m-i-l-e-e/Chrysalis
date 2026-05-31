#ifndef CHRYSALIS_PATTERN_H
#define CHRYSALIS_PATTERN_H

#include "Space.h"
#include "Outline.h"
#include "Argument.h"

namespace Chrysalis {
    class Pattern {
    public:
        explicit Pattern(const std::string& name, Space* space, Outline* outline);

        void addPoint(const std::string& name, double x, double y) const;
        void addPoint(const std::string& from, const std::string& to, const Argument<double>* angle, const Argument<double>* length) const;
        void addPoint(const std::string& from, const std::string& to, Space::Direction direction, const Argument<double>* length) const;

        void nextPoint(const std::string& to, const Argument<double>* angle, const Argument<double>* length) const;
        void nextPoint(const std::string& to, Space::Direction direction, const Argument<double>* length) const;

        void sharePoint(const std::string& point, const Pattern* pattern) const;

        std::vector<std::vector<float>> getOutline() const;
        std::vector<float> getShape() const;
    private:
        std::string name_;
        Space* space_;
        Outline* outline_;
    };
}

#endif //CHRYSALIS_PATTERN_H