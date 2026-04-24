#ifndef FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

class JsonUIExporterOptions: public BaseUIExporterOptions {
private:
    bool ignoreCSS;
    bool visibleOnly;
};


#endif //FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H