#ifndef FASHIONDESIGNAPPS_XMLUIEXPORTER_H
#define FASHIONDESIGNAPPS_XMLUIEXPORTER_H

#include "BaseUIExporter.h"
#include "XmlUIExporterOptions.h"

class XmlUIExporter: public BaseUIExporter {
public:
    explicit XmlUIExporter(XmlUIExporterOptions* options);
    ~XmlUIExporter() override;

    void exportUI() override;
    void exportUI(QWidget* widget) override;
    void exportUI(std::forward_list<QWidget*> widgets) override;

    BaseUIExporterOptions* getOptions() override;
private:
    XmlUIExporterOptions* options_;
};

#endif //FASHIONDESIGNAPPS_XMLUIEXPORTER_H