#ifndef FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

class XmlUIExporterOptions: public BaseUIExporterOptions {
public:
    explicit XmlUIExporterOptions();

    bool getExportIcons(QSettings* settings) const;
    bool getUICompatible(QSettings* settings) const;
private:
    bool exportIcons;
    bool uiCompatible;
};


#endif //FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H