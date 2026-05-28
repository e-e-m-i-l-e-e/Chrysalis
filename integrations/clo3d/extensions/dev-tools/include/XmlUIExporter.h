#ifndef CHRYSALIS_XMLUIEXPORTER_H
#define CHRYSALIS_XMLUIEXPORTER_H

#include "BaseUIExporter.h"
#include "XmlUIExporterOptions.h"

class XmlUIExporter: public BaseUIExporter {
public:
    explicit XmlUIExporter(XmlUIExporterOptions* options);
    ~XmlUIExporter() override;

    static XmlUIExporter* create();

    void exportUI(std::forward_list<QWidget*> widgets) override;
    BaseUIExporterOptions* getOptions() override;
private:
    XmlUIExporterOptions* options_;
};

#endif //CHRYSALIS_XMLUIEXPORTER_H