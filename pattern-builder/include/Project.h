#ifndef FASHIONDESIGNAPPS_PROJECT_H
#define FASHIONDESIGNAPPS_PROJECT_H

#include <string>
#include <forward_list>

#include "PatternBuilder.h"

class Project {
public:
    ~Project();
    PatternBuilder addPattern(const std::string& name);
private:
    std::forward_list<Pattern*> patterns_;
};

#endif //FASHIONDESIGNAPPS_PROJECT_H