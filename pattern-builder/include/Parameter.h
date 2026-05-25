#ifndef FASHIONDESIGNAPPS_PARAMETER_H
#define FASHIONDESIGNAPPS_PARAMETER_H

#include <string>

#include <boost/serialization/access.hpp>

#include "BaseArgument.h"

class Parameter: public BaseArgument {
    friend class boost::serialization::access;
public:
    explicit Parameter(const std::string& name, double value);

    double getValue() const override;
    void setValue(double value);

    [[nodiscard]] const std::string& getName() const;
private:
    double value_;
    std::string name_;

    template <class Archive>
    void serialize(Archive& archive, const unsigned int version) {
        archive & name_;
        archive & value_;
    }
};

#endif //FASHIONDESIGNAPPS_PARAMETER_H