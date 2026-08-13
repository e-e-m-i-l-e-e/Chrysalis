#ifndef CHRYSALIS_XMLUIEXPORTER_H
#define CHRYSALIS_XMLUIEXPORTER_H

#include "BaseUIExporter.h"
#include "XmlUIExporterOptions.h"

class XmlUIExporter: public BaseUIExporter {
public:
    explicit XmlUIExporter(std::unique_ptr<XmlUIExporterOptions> options);

    static XmlUIExporter* create();

    void exportUI(std::forward_list<QWidget*>&& widgets) override;
    BaseUIExporterOptions* getOptions() override;
private:
    std::unique_ptr<XmlUIExporterOptions> options_;
};

#endif //CHRYSALIS_XMLUIEXPORTER_H