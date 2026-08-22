#include "LocalServer.h"

#include <QLocalSocket>

#include "Logging.h"
#define LOGGER_NAME "Local Server"

using namespace CLO3D;

LocalServer::LocalServer() {
    QLocalServer::removeServer(SERVER_NAME);
    QObject::connect(&localServer, &QLocalServer::newConnection, [this]() -> void {
        while (localServer.hasPendingConnections()) {
            QLocalSocket* client = localServer.nextPendingConnection();
            QObject::connect(client, &QLocalSocket::readyRead, [this, client]() -> void {
                listeners_.begin()->second->receive(client->readAll());
            });
            QObject::connect(client, &QLocalSocket::disconnected, client, &QObject::deleteLater);
        }
    });
    if (!localServer.listen(SERVER_NAME)) {
        LOG_ERROR("Could not listen to {}: {}", SERVER_NAME, localServer.errorString().toStdString());
    } else {
        LOG_INFO("Listening on {} at: {}", SERVER_NAME, localServer.fullServerName().toStdString());
    }
}

void LocalServer::listen(std::unique_ptr<BaseLocalServerListener> listener) {
    listeners_.emplace("", std::move(listener));
}
