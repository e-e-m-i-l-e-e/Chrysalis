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

ParametersModel* ProjectElement::getParameters() const {
    return parameters_;
}

void ProjectElement::setParameters(ParametersModel* parameters) {
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
    const auto parameters = project->getParameters();
    const auto param1 = new Parameter("Back Waist Length");
    param1->setValue(42);
    const auto param2 = new Parameter("Back Width");
    param2->setValue(31);
    const auto param3 = new Parameter("Bust Height");
    param3->setValue(28);
    const auto param4 = new Parameter("Bust Span");
    param4->setValue(17);
    const auto param5 = new Parameter("Apex to center-front");
    param5->setValue(21);
    const auto param6 = new Parameter("Apex to shoulder");
    param6->setValue(27);
    const auto param7 = new Parameter("Hip Depth");
    param7->setValue(21.5);
    const auto param8 = new Parameter("Bust Circumference");
    param8->setValue(96);
    const auto param9 = new Parameter("Waist Circumference");
    param9->setValue(68);
    const auto param10 = new Parameter("Neck Circumference");
    param10->setValue(38);
    const auto param11 = new Parameter("Shoulder Length");
    param11->setValue(11);
    const auto param12 = new Parameter("Hip Circumference");
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