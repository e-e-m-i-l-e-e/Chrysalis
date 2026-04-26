#ifndef FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H

#include "BaseUIExporterOptions.h"

class XmlUIExporterOptions: public BaseUIExporterOptions {
public:
    explicit XmlUIExporterOptions(const QSettings* settings);

    bool getExportIcons() const;
    bool getUICompatible() const;
private:
    bool exportIcons;
    bool uiCompatible;
};


#endif //FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONS_H