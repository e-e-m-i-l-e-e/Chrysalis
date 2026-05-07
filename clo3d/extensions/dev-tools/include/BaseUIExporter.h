#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTER_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTER_H

#include <forward_list>

#include "BaseUIExporterOptions.h"

class BaseUIExporter {
protected:
    virtual ~BaseUIExporter() = default;
public:
    virtual void exportUI() = 0;
    virtual void exportUI(QWidget* widget) = 0;
    virtual void exportUI(std::forward_list<QWidget*> widgets) = 0;
    virtual BaseUIExporterOptions* getOptions() = 0;
};

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTER_H