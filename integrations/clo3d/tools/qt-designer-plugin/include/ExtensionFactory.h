#ifndef CHRYSALIS_EXTENSIONFACTORY_H
#define CHRYSALIS_EXTENSIONFACTORY_H

#include "QExtensionFactory"

namespace CLO3D::UI {
    class ExtensionFactory: public QExtensionFactory {
        Q_OBJECT
    public:
        explicit ExtensionFactory(QExtensionManager *parent);
    protected:
        QObject* createExtension(QObject *object, const QString &iid, QObject *parent) const override;
    };
}

#endif //CHRYSALIS_EXTENSIONFACTORY_H