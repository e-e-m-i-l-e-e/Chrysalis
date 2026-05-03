#ifndef FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

class GeneralUIExporterOptions: public BaseUIExporterOptions {
public:
    explicit GeneralUIExporterOptions();

    QKeySequence getShortcut(Settings& settings) const;
    bool getPickMyMouse(Settings& settings) const;
};

#endif //FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONS_H