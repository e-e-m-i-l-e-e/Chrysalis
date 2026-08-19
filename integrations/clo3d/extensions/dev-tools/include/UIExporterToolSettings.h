#ifndef CHRYSALIS_UIEXPORTERTOOLSETTINGS_H
#define CHRYSALIS_UIEXPORTERTOOLSETTINGS_H

#include <list>

#include "BaseUIExporterOptions.h"
#include "BaseExtensionSettings.h"

namespace CLO3D {
    class UIExporterToolSettings: public BaseExtensionSettings {
    public:
        void read() override;
        void write() override;

        void addOptions(BaseUIExporterOptions* options);

        [[nodiscard]] std::list<BaseUIExporterOptions*>::const_iterator begin() const;
        [[nodiscard]] std::list<BaseUIExporterOptions*>::const_iterator end() const;
    private:
        std::list<BaseUIExporterOptions*> options_;
    };
}

#endif //CHRYSALIS_UIEXPORTERTOOLSETTINGS_H