#ifndef FASHIONDESIGNAPPS_PROJECTPARAMETERS_H
#define FASHIONDESIGNAPPS_PROJECTPARAMETERS_H

#include <unordered_map>

#include "Parameter.h"

class ProjectParameters {
public:
    ~ProjectParameters();

    void addParameter(Parameter* parameter);
    Parameter* getParameter(const std::string& name);
private:
    std::unordered_map<std::string, Parameter*> parameters_;
};

#endif //FASHIONDESIGNAPPS_PROJECTPARAMETERS_H