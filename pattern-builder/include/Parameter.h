#ifndef FASHIONDESIGNAPPS_PARAMETER_H
#define FASHIONDESIGNAPPS_PARAMETER_H

#include <string>

#include "BaseArgument.h"

class Parameter: public BaseArgument {
public:
    explicit Parameter(const std::string& name, double value);

    double getValue() const override;
    void setValue(double value);

    [[nodiscard]] const std::string& getName() const;
private:
    double value_;
    std::string name_;
};

#endif //FASHIONDESIGNAPPS_PARAMETER_H