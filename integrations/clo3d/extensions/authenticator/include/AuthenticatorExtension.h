#ifndef CHRYSALIS_AUTHENTICATOREXTENSION_H
#define CHRYSALIS_AUTHENTICATOREXTENSION_H

#include "BaseExtension.h"

// Hook installation used to happen in install() here, but moved to
// ExtensionsManager::install() to keep a single, shared HooksManager
// registry across the DllMain shell / Core / plugin DLL split.
// See ExtensionsManager.cpp, guarded by EXTEND_WITH_AUTHENTICATOR.
class AuthenticatorExtension: public BaseExtension {
public:
    void install() override;
};

#endif //CHRYSALIS_AUTHENTICATOREXTENSION_H