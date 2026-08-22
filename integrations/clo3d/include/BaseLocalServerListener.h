#ifndef CHRYSALIS_BASELOCALSERVERLISTENER_H
#define CHRYSALIS_BASELOCALSERVERLISTENER_H

#include <QByteArray>

namespace CLO3D {
    class BaseLocalServerListener {
    public:
        virtual ~BaseLocalServerListener() = default;
        virtual void receive(QByteArray message) = 0;
    protected:
        explicit BaseLocalServerListener() = default;
    };
}

#endif // CHRYSALIS_BASELOCALSERVERLISTENER_H
