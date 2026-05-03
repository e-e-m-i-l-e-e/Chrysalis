#ifndef FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

class JsonUIExporterOptions: public BaseUIExporterOptions {
public:
    explicit JsonUIExporterOptions();

    bool getVisibleOnly(Settings& settings) const;
    bool getIgnoreCSS(Settings& settings) const;
private:
    bool ignoreCSS;
    bool visibleOnly;
};


#endif //FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H