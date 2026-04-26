#ifndef FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

class GeneralUIExporterOptions: public BaseUIExporterOptions {
public:
    explicit GeneralUIExporterOptions(const QSettings* settings);

    QKeySequence getShortcut() const;
    bool getPickMyMouse() const;
};

#endif //FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONS_H