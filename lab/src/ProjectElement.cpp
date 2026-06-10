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

#include "HARDCODED_PROJECTS.h"

void ProjectElement::createProject() {
    delete project;
    project = Project::create();
    setupProject1(project);
    parameters_->setParameters(project->getParameters());
    emit projectChanged();
}

void ProjectElement::openProject(const QUrl& filePath) {
    project = Project::read(filePath.toLocalFile().toUtf8().constData());
    project->getInstructions()->execute();
    parameters_->setParameters(project->getParameters());
    setFilePath(filePath);
    std::cout << "Patterns size: " << project->getPatterns()->count() << std::endl;
    for (int i = 0; i < project->getPatterns()->count(); ++i)
    {
        std::cout << "Pattern: " << project->getPatterns()->at(i)->getName() << std::endl;
        for (const auto [name, point]: project->getPatterns()->at(i)->getSpace()->getPoints())
        {
            std::cout << name << ": (" << point->x() << ", " << point->y() << ")" << std::endl;
        }
        for (const auto& outline: *project->getPatterns()->at(i)->getSpace()->getOutline())
        {
            for (const auto& pointName: outline->getPoints())
            {
                std::cout << pointName << ": (" << project->getPatterns()->at(i)->getSpace()->getPoint(pointName)->x() << ", " << project->getPatterns()->at(i)->getSpace()->getPoint(pointName)->y() << ")" << std::endl;
            }
        }
    }
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