#include "ChrysalisPatternProjectElement.h"

ChrysalisPatternProjectElement::ChrysalisPatternProjectElement(QQuickItem* parent): QQuickItem(parent) {}

ChrysalisPatternProjectElement::~ChrysalisPatternProjectElement() {
    delete project;
}

QString ChrysalisPatternProjectElement::getName() const {
    return project->getName().data();
}

QUrl ChrysalisPatternProjectElement::getFilePath() const {
    return filePath_;
}

void ChrysalisPatternProjectElement::setName(const QString& name) {
    project->setName(name.toStdString());
    emit nameChanged();
}

void ChrysalisPatternProjectElement::setFilePath(const QUrl& filePath) {
    filePath_ = filePath;
    emit filePathChanged();
}

PatternParametersModel* ChrysalisPatternProjectElement::getParameters() const {
    return parameters_;
}

void ChrysalisPatternProjectElement::setParameters(PatternParametersModel* parameters) {
    parameters_ = parameters;
    if (project) parameters_->setParameters(project->getParameters());
    emit parametersChanged();
}

bool ChrysalisPatternProjectElement::hasProject() const {
    return project != nullptr;
}

void ChrysalisPatternProjectElement::createProject() {
    delete project;
    project = PB::Project::create();
    const auto parameters = project->getParameters();
    parameters->addParameter(new Parameter("Test", 1));
    parameters_->setParameters(project->getParameters());
    emit projectChanged();
}

void ChrysalisPatternProjectElement::openProject(const QUrl& filePath) {
    project = archive.read(filePath.toLocalFile().toUtf8().constData());
    parameters_->setParameters(project->getParameters());
    setFilePath(filePath);
    emit nameChanged();
    emit projectChanged();
}


void ChrysalisPatternProjectElement::saveProject(const QUrl& filePath) {
    archive.write(filePath.toLocalFile().toUtf8().data(), project);
    setFilePath(filePath);
}

void ChrysalisPatternProjectElement::closeProject() {
    delete project;
    project = nullptr;
    emit projectChanged();
}