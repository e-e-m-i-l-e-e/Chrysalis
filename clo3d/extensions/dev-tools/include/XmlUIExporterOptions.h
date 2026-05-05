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
    void write(const Settings &settings) override;

    [[nodiscard]] bool getIsEnabled() const;
    [[nodiscard]] bool getExportIcons() const;
    [[nodiscard]] bool getUICompatible() const;

    void setIsEnabled(bool isEnabled);
    void setExportIcons(bool exportIcons);
    void setUICompatible(bool uiCompatible);
private:
    bool isEnabled_ = Defaults::IS_ENABLED;
    bool exportIcons_ = Defaults::EXPORT_ICONS;
    bool uiCompatible_ = Defaults::UI_COMPATIBLE;
};


#endif //FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H