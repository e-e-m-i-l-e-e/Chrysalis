#ifndef CHRYSALIS_BASEEXTENSION_H
#define CHRYSALIS_BASEEXTENSION_H

#include "CommandRunner.h"
#include "ExtensionsSettingsDialog.h"

class BaseExtension {
public:
    virtual ~BaseExtension() = default;

    virtual void install() {}
    virtual void startup() {}
    virtual void configure(QWidget* widget) {}
    virtual void configureMenu(QMenu* extensionMenu) {}
    virtual void configureStatusBar(QWidget* parent) {}
    virtual void configureCommands(CommandRunner* container) {}
    virtual void configureSettings(ExtensionsSettings* extensionsSettings) {}
    virtual void configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) {}
};

#endif //CHRYSALIS_BASEEXTENSION_H