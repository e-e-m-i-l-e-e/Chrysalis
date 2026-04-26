#ifndef FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

class JsonUIExporterOptions: public BaseUIExporterOptions {
public:
    explicit JsonUIExporterOptions(const QSettings* settings);

    bool getVisibleOnly() const;
    bool getIgnoreCSS() const;
private:
    bool ignoreCSS;
    bool visibleOnly;
};


#endif //FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONS_H