#ifndef FASHIONDESIGNAPPS_BASEEXTENSION_H
#define FASHIONDESIGNAPPS_BASEEXTENSION_H

#include <QMenu>

#include "ExtensionsSettingsDialog.h"

class BaseExtension {
protected:
    virtual ~BaseExtension() = default;
public:
    virtual void install() {}
    virtual void configure(QWidget* widget) {}
    virtual void configureMenu(QMenu* extensionMenu) {}
    virtual void configureSettings(ExtensionsSettings* extensionsSettings) {}
    virtual void configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) {}
    virtual void configureStatusBar(QWidget* parent) {}
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSION_H