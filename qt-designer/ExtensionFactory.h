#ifndef CLOEXTENSIONS_EXTENSIONFACTORY_H
#define CLOEXTENSIONS_EXTENSIONFACTORY_H

#include "QExtensionFactory"

class ExtensionFactory: public QExtensionFactory {
    Q_OBJECT
public:
    explicit ExtensionFactory(QExtensionManager *parent, int count);
protected:
    QObject* createExtension(QObject *object, const QString &iid, QObject *parent) const override;
private:
    int count_;
};

#endif //CLOEXTENSIONS_EXTENSIONFACTORY_H