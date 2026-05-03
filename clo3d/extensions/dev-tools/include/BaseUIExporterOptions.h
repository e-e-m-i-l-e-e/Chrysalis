#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H

#include <QDir>

#include "Settings.h"

class BaseUIExporterOptions {
protected:
    virtual ~BaseUIExporterOptions() = default;
public:
    QDir getRootFolder(const Settings& settings);
    QString getFileName(Settings& settings);
    QString getObjectName(Settings& settings);
    QString getClassName(Settings& settings);

    void setRootFolder(Settings& settings, const QDir& rootFolder);
    void setFileName(Settings& settings, const QString& fileName);
    void setObjectName(Settings& settings, const QString& objectName);
    void setClassName(Settings& settings, const QString& className);
};

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H