#ifndef FASHIONDESIGNAPPS_PATTERN_H
#define FASHIONDESIGNAPPS_PATTERN_H

#include "BaseArgument.h"
#include "Space.h"
#include "DartBuilder.h"
#include "OutlineBuilder.h"

namespace PB {
    class Pattern {
    public:
        explicit Pattern(const std::string& name, Space* space, Outline* outline);

        void addPoint(const std::string& name, double x, double y) const;
        void addPoint(const std::string& from, const std::string& to, const BaseArgument* angle, const BaseArgument* length) const;
        void addPoint(const std::string& from, const std::string& to, Space::Direction direction, const BaseArgument* length) const;

        void nextPoint(const std::string& to, const BaseArgument* angle, const BaseArgument* length) const;
        void nextPoint(const std::string& to, Space::Direction direction, const BaseArgument* length) const;

        void sharePoint(const std::string& point, const Pattern* pattern) const;

        DartBuilder startDart() const;
        OutlineBuilder editOutline() const;

        std::vector<std::vector<float>> getOutline() const;
        std::vector<float> getShape() const;
    private:
        std::string name_;
        Space* space_;
        Outline* outline_;
    };
}

#endif //FASHIONDESIGNAPPS_PATTERN_H