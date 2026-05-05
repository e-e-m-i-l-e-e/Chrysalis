#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H

#include <QDir>

#include "Settings.h"

class BaseUIExporterOptions {
    struct Keys {
        inline static const QString ROOT_FOLDER = "rootFolder";
        inline static const QString FILE_NAME = "fileName";
        inline static const QString OBJECT_NAME = "objectName";
        inline static const QString CLASS_NAME = "className";
    };
    struct Defaults {
        inline static const QDir ROOT_FOLDER = QDir(QString(CLO_HOME) + "/.extensions");
        inline static const QString FILE_NAME = "ui";
        inline static const QString OBJECT_NAME = "";
        inline static const QString CLASS_NAME = "";
    };
protected:
    BaseUIExporterOptions() = default;
    virtual ~BaseUIExporterOptions() = default;
public:
    virtual void read(const Settings& settings);

    [[nodiscard]] QDir getRootFolder() const;
    [[nodiscard]] QString getFileName() const;
    [[nodiscard]] QString getObjectName() const;
    [[nodiscard]] QString getClassName() const;

    void setRootFolder(const Settings& settings, const QDir& rootFolder);
    void setFileName(const Settings& settings, const QString& fileName);
    void setObjectName(const Settings& settings, const QString& objectName);
    void setClassName(const Settings& settings, const QString& className);
private:
    QDir rootFolder_ = Defaults::ROOT_FOLDER;
    QString fileName_ = Defaults::FILE_NAME;
    QString objectName_ = Defaults::OBJECT_NAME;
    QString className_ = Defaults::CLASS_NAME;
};

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H