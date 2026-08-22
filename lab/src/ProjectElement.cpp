#include "ProjectElement.h"

#include <QUrl>
#include <QString>
#include <QQuickItem>
#include <QLocalSocket>

#include "Logging.h"
#include "ParametersElement.h"
#include "exceptions/ProjectIOError.h"
#include "projects/Project1Composer.h"

#define LOGGER_NAME "Project Element"

using namespace Chrysalis;

ProjectElement::ProjectElement(QQuickItem* parent): QQuickItem(parent) {}

QString ProjectElement::getName() const {
    return project_->getName().data();
}

QUrl ProjectElement::getFilePath() const {
    return filePath_;
}

void ProjectElement::setName(const QString& name) {
    project_->setName(name.toStdString());
    emit nameChanged();
}

void ProjectElement::setFilePath(const QUrl& filePath) {
    filePath_ = filePath;
    emit filePathChanged();
}

ParametersElement* ProjectElement::getParameters() const {
    return parameters_;
}

void ProjectElement::setParameters(ParametersElement* parameters) {
    parameters_ = parameters;
    if (project_) parameters_->setParameters(project_->getParameters());
    emit parametersChanged();
}

bool ProjectElement::hasProject() const {
    return project_ != nullptr;
}

void ProjectElement::execute() const {
    project_->execute();
}

void ProjectElement::sendToCLO3D() const {
    const auto socket = new QLocalSocket();
    connect(socket, &QLocalSocket::disconnected, socket, &QObject::deleteLater);
    socket->connectToServer("CLO3D");
    if (!socket->waitForConnected(1000)) {
        LOG_ERROR("Failed to connect to CLO3D: {}", socket->errorString().toStdString());
        socket->deleteLater();
        return;
    }
    const std::vector<char> buffer = project_->bytes();
    if (const QByteArray message(buffer.data(), buffer.size());
        socket->write(message) == -1 || !socket->waitForBytesWritten(1000)) {
        LOG_ERROR("Failed to send project to CLO3D: {}", socket->errorString().toStdString());
    } else {
        LOG_INFO("Project has been sent to CLO3D.");
    }
    socket->flush();
    socket->disconnectFromServer();
}

void ProjectElement::createProject() {
    project_ = Project::create();
    Project1Composer composer(project_.get());
    composer.fill();
    parameters_->setParameters(project_->getParameters());
    emit projectChanged(project_.get());
}

void ProjectElement::openProject(const QUrl& filePath) {
    try {
        project_ = Project::read(filePath.toLocalFile().toUtf8().constData());
    } catch (const ProjectIOError& e) {
        LOG_ERROR("{}", e.what());
        return;
    }
    project_->execute();
    parameters_->setParameters(project_->getParameters());
    setFilePath(filePath);
    emit nameChanged();
    emit projectChanged(project_.get());
}


void ProjectElement::saveProject(const QUrl& filePath) {
    Project::write(filePath.toLocalFile().toUtf8().data(), *project_);
    setFilePath(filePath);
}

void ProjectElement::closeProject() {
    project_ = nullptr;
    emit projectChanged(project_.get());
}