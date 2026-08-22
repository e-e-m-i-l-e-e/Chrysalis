#ifndef CHRYSALIS_LOCALSERVERLISTENER_H
#define CHRYSALIS_LOCALSERVERLISTENER_H

#include "BaseLocalServerListener.h"

namespace CLO3D {
    class LocalServerListener: public BaseLocalServerListener {
    public:
        void receive(QByteArray message) override;
    };
}

#endif // CHRYSALIS_LOCALSERVERLISTENER_H
