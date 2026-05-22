#ifndef FASHIONDESIGNAPPS_PARAMETER_H
#define FASHIONDESIGNAPPS_PARAMETER_H

#include <string>

class Parameter {
public:
    explicit Parameter(const std::string& name, double value);

    double getValue() const;
    void setValue(double value);
private:
    double value_;
    std::string name_;
};

#endif //FASHIONDESIGNAPPS_PARAMETER_H