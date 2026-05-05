#ifndef FASHIONDESIGNAPPS_UIEXPORTER_H
#define FASHIONDESIGNAPPS_UIEXPORTER_H

#include "BaseExtensionsSettingsEditor.h"

class BaseUIExporter: public BaseExtensionsSettingsEditor {
public:
    virtual void exportUI() = 0;
};

#endif //FASHIONDESIGNAPPS_UIEXPORTER_H