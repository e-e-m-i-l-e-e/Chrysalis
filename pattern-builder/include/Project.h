#ifndef FASHIONDESIGNAPPS_PROJECT_H
#define FASHIONDESIGNAPPS_PROJECT_H

#include <forward_list>

#include "Pattern.h"

class Project {
public:
    ~Project();
    Pattern* createPattern(const std::string& name);
private:
    std::forward_list<Pattern*> patterns_;
};

#endif //FASHIONDESIGNAPPS_PROJECT_H