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
    const auto param1 = new Chrysalis::Parameter("Back Waist Length");
    param1->setValue(42);
    const auto param2 = new Chrysalis::Parameter("Back Width");
    param2->setValue(31);
    const auto param3 = new Chrysalis::Parameter("Bust Height");
    param3->setValue(28);
    const auto param4 = new Chrysalis::Parameter("Bust Span");
    param4->setValue(17);
    const auto param5 = new Chrysalis::Parameter("Apex to center-front");
    param5->setValue(21);
    const auto param6 = new Chrysalis::Parameter("Apex to shoulder");
    param6->setValue(27);
    const auto param7 = new Chrysalis::Parameter("Hip Depth");
    param7->setValue(21.5);
    const auto param8 = new Chrysalis::Parameter("Bust Circumference");
    param8->setValue(96);
    const auto param9 = new Chrysalis::Parameter("Waist Circumference");
    param9->setValue(68);
    const auto param10 = new Chrysalis::Parameter("Neck Circumference");
    param10->setValue(38);
    const auto param11 = new Chrysalis::Parameter("Shoulder Length");
    param11->setValue(11);
    const auto param12 = new Chrysalis::Parameter("Hip Circumference");
    param12->setValue(98);
    parameters->addParameter(param1);
    parameters->addParameter(param2);
    parameters->addParameter(param3);
    parameters->addParameter(param4);
    parameters->addParameter(param5);
    parameters->addParameter(param6);
    parameters->addParameter(param7);
    parameters->addParameter(param8);
    parameters->addParameter(param9);
    parameters->addParameter(param10);
    parameters->addParameter(param11);
    parameters->addParameter(param12);
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