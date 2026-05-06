#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTER_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTER_H

#include "BaseUIExporterOptions.h"

class BaseUIExporter {
protected:
    virtual ~BaseUIExporter() = default;
public:
    virtual void exportUI() = 0;
    virtual BaseUIExporterOptions* getOptions() = 0;
};

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTER_H