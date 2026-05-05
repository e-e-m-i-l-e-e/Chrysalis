#ifndef FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

class XmlUIExporterOptions: public BaseUIExporterOptions {
    struct Keys {
        inline static const QString IS_ENABLED = "isEnabled";
        inline static const QString EXPORT_ICONS = "exportIcons";
        inline static const QString UI_COMPATIBLE = "uiCompatible";
    };
    struct Defaults {
        static constexpr bool IS_ENABLED = true;
        static constexpr bool EXPORT_ICONS = false;
        static constexpr bool UI_COMPATIBLE = false;
    };
public:
    void read(const Settings &settings) override;

    [[nodiscard]] bool getIsEnabled() const;
    [[nodiscard]] bool getExportIcons() const;
    [[nodiscard]] bool getUICompatible() const;

    void setIsEnabled(const Settings& settings, bool isEnabled);
    void setExportIcons(const Settings& settings, bool exportIcons);
    void setUICompatible(const Settings& settings, bool uiCompatible);
private:
    bool isEnabled_ = Defaults::IS_ENABLED;
    bool exportIcons_ = Defaults::EXPORT_ICONS;
    bool uiCompatible_ = Defaults::UI_COMPATIBLE;
};


#endif //FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H