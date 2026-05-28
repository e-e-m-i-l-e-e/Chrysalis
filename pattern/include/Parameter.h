#ifndef FASHIONDESIGNAPPS_PARAMETER_H
#define FASHIONDESIGNAPPS_PARAMETER_H

#include <string>

#include <boost/serialization/access.hpp>

#include "BaseArgument.h"

class Parameter;

namespace boost::serialization {
    template<class Archive>
    void save_construct_data(Archive&, const Parameter*, const unsigned int);

    template<class Archive>
    void load_construct_data(Archive&, Parameter*, const unsigned int);
}

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
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive&, const Parameter*, const unsigned int);

    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive&, Parameter*, const unsigned int);
};

#endif //FASHIONDESIGNAPPS_PARAMETER_H