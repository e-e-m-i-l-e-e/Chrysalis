#ifndef CHRYSALIS_DEVTOOLSEXTENSION_H
#define CHRYSALIS_DEVTOOLSEXTENSION_H

#include "BaseDevTool.h"
#include "BaseExtension.h"
#include "UIExporterTool.h"

namespace CLO3D {
    class DevToolsExtension: public BaseExtension {
    public:
        ~DevToolsExtension() override;

        static DevToolsExtension* create();

        void addDevTool(BaseDevTool* tool);

        void startup() override;
        void configureCommands(CommandRunner* runner) override;
        void configureSettings(ExtensionsSettings* extensionsSettings) override;
        void configureSettingsUI(UI::ExtensionsSettingsDialog *extensionsSettingsDialog) override;
    private:
        std::list<BaseDevTool*> devTools_;
    };
}

#endif //CHRYSALIS_DEVTOOLSEXTENSION_H