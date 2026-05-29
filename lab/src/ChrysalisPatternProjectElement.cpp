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
    project = Chrysalis::Project::create();
    const auto parameters = project->getParameters();
    parameters->addParameter(new Chrysalis::Parameter("Back Waist Length", 42));
    parameters->addParameter(new Chrysalis::Parameter("Back Width", 31));
    parameters->addParameter(new Chrysalis::Parameter("Bust Height", 28));
    parameters->addParameter(new Chrysalis::Parameter("Bust Span", 17));
    parameters->addParameter(new Chrysalis::Parameter("Apex to center-front", 21));
    parameters->addParameter(new Chrysalis::Parameter("Apex to shoulder", 27));
    parameters->addParameter(new Chrysalis::Parameter("Hip Depth", 21.5));
    parameters->addParameter(new Chrysalis::Parameter("Bust Circumference", 96));
    parameters->addParameter(new Chrysalis::Parameter("Waist Circumference", 68));
    parameters->addParameter(new Chrysalis::Parameter("Neck Circumference", 38));
    parameters->addParameter(new Chrysalis::Parameter("Shoulder Length", 11));
    parameters->addParameter(new Chrysalis::Parameter("Hip Circumference", 98));
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