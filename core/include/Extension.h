#ifndef CLOEXTENSIONS_EXTENSION_H
#define CLOEXTENSIONS_EXTENSION_H

#include "ExtensionsManager.h"

class Extension {
protected:
    explicit Extension() {
        ExtensionsManager::extensions.push_back(this);
    }
    virtual ~Extension() = default;
public:
    virtual void configureMenu(QMenu* extensionMenu) {}
};

#endif //CLOEXTENSIONS_EXTENSION_H