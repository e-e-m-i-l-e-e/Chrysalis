#ifndef FASHIONDESIGNAPPS_PROJECTPARAMETERS_H
#define FASHIONDESIGNAPPS_PROJECTPARAMETERS_H

#include <unordered_map>

#include <boost/serialization/unordered_map.hpp>

#include "Parameter.h"

class ProjectParameters {
    friend class boost::serialization::access;
public:
    ~ProjectParameters();

    [[nodiscard]] unsigned int count() const;
    void addParameter(Parameter* parameter);
    Parameter* getParameter(const std::string& name);
private:
    std::unordered_map<std::string, Parameter*> parameters_;

    template <class Archive>
    void serialize(Archive& archive, const unsigned int version) {
        archive & parameters_;
    }
};

#endif //FASHIONDESIGNAPPS_PROJECTPARAMETERS_H