#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGE_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGE_H

class BaseExtensionsSettingsPage {
public:
    virtual ~BaseExtensionsSettingsPage() = default;

    virtual void save() = 0;
    virtual void reset() = 0;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGE_H