#ifndef CHRYSALIS_EXTENSIONSSETTINGS_H
#define CHRYSALIS_EXTENSIONSSETTINGS_H

#include "BaseExtensionSettings.h"

class ExtensionsSettings {
public:
    explicit ExtensionsSettings(QSettings* settings);
    ~ExtensionsSettings();

    void read() const;
    void clear() const;
    void addSettings(BaseExtensionSettings* settings);
private:
    /// @uml{composition}
    QSettings* settings_;
    std::forward_list<BaseExtensionSettings*> extensionsSettings_;
};

#endif //CHRYSALIS_EXTENSIONSSETTINGS_H