#include "ProjectElement.h"

using namespace Chrysalis;

ProjectElement::ProjectElement(QQuickItem* parent): QQuickItem(parent) {}

ProjectElement::~ProjectElement() {
    delete project;
}

QString ProjectElement::getName() const {
    return project->getName().data();
}

QUrl ProjectElement::getFilePath() const {
    return filePath_;
}

void ProjectElement::setName(const QString& name) {
    project->setName(name.toStdString());
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
    if (project) parameters_->setParameters(project->getParameters());
    emit parametersChanged();
}

bool ProjectElement::hasProject() const {
    return project != nullptr;
}

void ProjectElement::createProject() {
    delete project;
    project = Project::create();
    emit projectChanged();
}

void ProjectElement::openProject(const QUrl& filePath) {
    project = Project::read(filePath.toLocalFile().toUtf8().constData());
    parameters_->setParameters(project->getParameters());
    setFilePath(filePath);
    emit nameChanged();
    emit projectChanged();
}


void ProjectElement::saveProject(const QUrl& filePath) {
    Project::write(filePath.toLocalFile().toUtf8().data(), project);
    setFilePath(filePath);
}

void ProjectElement::closeProject() {
    delete project;
    project = nullptr;
    emit projectChanged();
}