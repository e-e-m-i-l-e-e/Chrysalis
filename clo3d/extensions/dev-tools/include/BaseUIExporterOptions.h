#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H

#include <QDir>

class BaseUIExporterOptions {
private:
    QDir rootDir;
    QString fileName;
    QString className;
    QString objectName;
};

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONS_H