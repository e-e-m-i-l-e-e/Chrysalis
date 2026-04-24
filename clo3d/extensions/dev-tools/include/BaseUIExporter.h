#ifndef FASHIONDESIGNAPPS_UIEXPORTER_H
#define FASHIONDESIGNAPPS_UIEXPORTER_H

class BaseUIExporter {
public:
    BaseUIExporter();
    virtual ~BaseUIExporter() = default;
    virtual void exportUI() = 0;
};


#endif //FASHIONDESIGNAPPS_UIEXPORTER_H