#ifndef FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

class JsonUIExporterOptions: public BaseUIExporterOptions {
    struct Keys {
        inline static const QString IS_ENABLED = "isEnabled";
        inline static const QString IGNORE_CSS = "ignoreCSS";
        inline static const QString VISIBLE_ONLY = "visibleOnly";
    };
    struct Defaults {
        static constexpr bool IS_ENABLED = true;
        static constexpr bool IGNORE_CSS = false;
        static constexpr bool VISIBLE_ONLY = false;
    };
public:
    void read(const Settings &settings) override;

    [[nodiscard]] bool getIsEnabled() const;
    [[nodiscard]] bool getIgnoreCSS() const;
    [[nodiscard]] bool getVisibleOnly() const;

    void setIsEnabled(const Settings& settings, bool isEnabled);
    void setIgnoreCSS(const Settings& settings, bool ignoreCSS);
    void setVisibleOnly(const Settings& settings, bool visibleOnly);
private:
    bool isEnabled_ = Defaults::IS_ENABLED;
    bool ignoreCSS_ = Defaults::IGNORE_CSS;
    bool visibleOnly_ = Defaults::VISIBLE_ONLY;
};

#endif //FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H