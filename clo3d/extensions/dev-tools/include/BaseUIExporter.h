#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTER_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTER_H

#include "BaseUIExporterOptions.h"

class BaseUIExporter {
public:
    virtual ~BaseUIExporter() = default;

    virtual void exportUI() = 0;
    virtual BaseUIExporterOptions* getOptions() = 0;
};

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTER_H