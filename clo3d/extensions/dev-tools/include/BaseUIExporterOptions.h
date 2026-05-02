#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H

#include <QDir>
#include <QSettings>

class BaseUIExporterOptions {
protected:
    virtual ~BaseUIExporterOptions() = default;
public:
    QDir getRootFolder(const QSettings* settings);
    QString getFileName(QSettings* settings);
    QString getObjectName(QSettings* settings);
    QString getClassName(QSettings* settings);

    void setRootFolder(QSettings* settings, const QDir& rootFolder);
    void setFileName(QSettings* settings, const QString& fileName);
    void setObjectName(QSettings* settings, const QString& objectName);
    void setClassName(QSettings* settings, const QString& className);
};

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H