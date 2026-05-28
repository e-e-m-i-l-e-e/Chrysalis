#ifndef CHRYSALIS_JSONUIEXPORTER_H
#define CHRYSALIS_JSONUIEXPORTER_H

#include "BaseUIExporter.h"
#include "JsonUIExporterOptions.h"

class JsonUIExporter: public BaseUIExporter {
public:
    explicit JsonUIExporter(JsonUIExporterOptions* options);
    ~JsonUIExporter() override;

    static JsonUIExporter* create();

    void exportUI(std::forward_list<QWidget*> widgets) override;
    BaseUIExporterOptions* getOptions() override;
private:
    QJsonObject getWidgetJson(const QWidget* widget);
    static QJsonObject getObjectJson(const QObject* object);

    JsonUIExporterOptions* options_;
};

#endif //CHRYSALIS_JSONUIEXPORTER_H