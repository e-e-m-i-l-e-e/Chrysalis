#ifndef FASHIONDESIGNAPPS_XMLUIEXPORTER_H
#define FASHIONDESIGNAPPS_XMLUIEXPORTER_H

#include "BaseUIExporter.h"
#include "XmlUIExporterOptions.h"

class XmlUIExporter: public BaseUIExporter {
public:
    explicit XmlUIExporter(XmlUIExporterOptions* options);
    ~XmlUIExporter() override;

    void exportUI() override;
    BaseUIExporterOptions* getOptions() override;
private:
    XmlUIExporterOptions* options_;
};

#endif //FASHIONDESIGNAPPS_XMLUIEXPORTER_H