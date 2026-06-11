#include "ProjectElement.h"

using namespace Chrysalis;

ProjectElement::ProjectElement(QQuickItem* parent): QQuickItem(parent) {}

ProjectElement::~ProjectElement() {
    delete project_;
}

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

#include "HARDCODED_PROJECTS.h"

void ProjectElement::createProject() {
    delete project_;
    project_ = Project::create();
    setupProject1(project_);
    parameters_->setParameters(project_->getParameters());
    emit projectChanged(project_);
}

void ProjectElement::openProject(const QUrl& filePath) {
    project_ = Project::read(filePath.toLocalFile().toUtf8().constData());
    project_->getInstructions()->execute();
    parameters_->setParameters(project_->getParameters());
    setFilePath(filePath);
    emit nameChanged();
    emit projectChanged(project_);
}


void ProjectElement::saveProject(const QUrl& filePath) {
    Project::write(filePath.toLocalFile().toUtf8().data(), project_);
    setFilePath(filePath);
}

void ProjectElement::closeProject() {
    delete project_;
    project_ = nullptr;
    emit projectChanged(project_);
}