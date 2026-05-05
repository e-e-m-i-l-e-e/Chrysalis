#ifndef FASHIONDESIGNAPPS_JSONUIEXPORTER_H
#define FASHIONDESIGNAPPS_JSONUIEXPORTER_H

#include "BaseUIExporter.h"
#include "JsonUIExporterOptions.h"

class JsonUIExporter: public BaseUIExporter {
public:
    explicit JsonUIExporter(JsonUIExporterOptions* options);
    ~JsonUIExporter() override;

    void exportUI() override;
    BaseUIExporterOptions* getOptions() override;
private:
    JsonUIExporterOptions* options_;
};

#endif //FASHIONDESIGNAPPS_JSONUIEXPORTER_H