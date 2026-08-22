#ifndef CHRYSALIS_LOCALSERVER_H
#define CHRYSALIS_LOCALSERVER_H

#include <QLocalServer>

#include "CLO3DExtensionExport.h"
#include "BaseLocalServerListener.h"

namespace CLO3D {
    class CLO3D_EXTENSION LocalServer {
    public:
        explicit LocalServer();
        void listen(std::unique_ptr<BaseLocalServerListener> listener);
    private:
        static constexpr auto SERVER_NAME = "CLO3D";

        QLocalServer localServer;
        std::unordered_map<std::string, std::unique_ptr<BaseLocalServerListener>> listeners_;
    };
}

#endif // CHRYSALIS_LOCALSERVER_H
