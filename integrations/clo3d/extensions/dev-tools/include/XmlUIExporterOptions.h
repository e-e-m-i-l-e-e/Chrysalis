#ifndef CHRYSALIS_XMLUIEXPORTEROPTIONS_H
#define CHRYSALIS_XMLUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

namespace CLO3D {
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
        bool isEnabled() override;

        void read(const QSettings* settings) override;
        void write(QSettings* settings) override;

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
}

#endif //CHRYSALIS_XMLUIEXPORTEROPTIONS_H