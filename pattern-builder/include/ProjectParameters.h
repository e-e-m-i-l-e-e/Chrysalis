#ifndef FASHIONDESIGNAPPS_PROJECTPARAMETERS_H
#define FASHIONDESIGNAPPS_PROJECTPARAMETERS_H

#include <vector>

#include "Parameter.h"

class ProjectParameters {
public:
    ~ProjectParameters();

    void addParameter(Parameter* parameter);
private:
    std::vector<Parameter*> parameters_;
};

#endif //FASHIONDESIGNAPPS_PROJECTPARAMETERS_H