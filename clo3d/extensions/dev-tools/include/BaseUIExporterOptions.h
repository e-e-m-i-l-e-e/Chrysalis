#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H

#include <QDir>
#include <QSettings>

class BaseUIExporterOptions {
protected:
    BaseUIExporterOptions(const QSettings* settings);
    virtual ~BaseUIExporterOptions();
public:
    QDir getRootFolder();
    QString getFileName();
    QString getObjectName();
    QString getClassName();
private:
    const QSettings* settings_;
};

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H