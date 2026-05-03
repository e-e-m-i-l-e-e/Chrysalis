#ifndef FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

class XmlUIExporterOptions: public BaseUIExporterOptions {
public:
    explicit XmlUIExporterOptions();

    bool getExportIcons(Settings& settings) const;
    bool getUICompatible(Settings& settings) const;
private:
    bool exportIcons;
    bool uiCompatible;
};


#endif //FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H