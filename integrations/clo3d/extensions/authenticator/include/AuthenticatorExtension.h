#ifndef CHRYSALIS_AUTHENTICATOREXTENSION_H
#define CHRYSALIS_AUTHENTICATOREXTENSION_H

#include "BaseExtension.h"

class AuthenticatorExtension: public BaseExtension {
public:
    void install() override;
};

#endif //CHRYSALIS_AUTHENTICATOREXTENSION_H