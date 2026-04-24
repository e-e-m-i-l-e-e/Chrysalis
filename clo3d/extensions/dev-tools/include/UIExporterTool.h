#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOL_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOL_H

#include <forward_list>

#include "BaseUIExporter.h"

class UIExporterTool {
public:

private:
    std::forward_list<BaseUIExporter*> exporters;
};

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOL_H