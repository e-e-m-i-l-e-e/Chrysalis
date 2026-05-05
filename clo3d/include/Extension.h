#ifndef CLOEXTENSIONS_EXTENSION_H
#define CLOEXTENSIONS_EXTENSION_H

#include <QMenu>

#include "ExtensionsSettingsDialog.h"

class Extension {
protected:
    explicit Extension() = default;
    virtual ~Extension() = default;
public:
    virtual void install() {}
    virtual void configure(QWidget* widget) {}
    virtual void configureMenu(QMenu* extensionMenu) {}
    virtual void configureSettings(ExtensionsSettings* extensionsSettings) {}
    virtual void configureStatusBar(QWidget* parent) {}
};

#endif //CLOEXTENSIONS_EXTENSION_H