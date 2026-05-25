#include "ChrysalisPatternProjectElement.h"

ChrysalisPatternProjectElement::ChrysalisPatternProjectElement(QQuickItem* parent): QQuickItem(parent) {}

ChrysalisPatternProjectElement::~ChrysalisPatternProjectElement() {
    delete project;
}

bool ChrysalisPatternProjectElement::hasProject() const {
    return project != nullptr;
}

void ChrysalisPatternProjectElement::createProject() {
    delete project;
    project = PB::Project::create();
    emit projectChanged();
}

void ChrysalisPatternProjectElement::openProject(const QUrl& filePath) {
    project = archive.read(filePath.toLocalFile().toUtf8().constData());
    std::cout << project->name << std::endl;
    emit projectChanged();
}


void ChrysalisPatternProjectElement::saveProject(const QUrl& filePath) {
    archive.write(filePath.toLocalFile().toUtf8().data(), project);
}

void ChrysalisPatternProjectElement::closeProject() {
    delete project;
    project = nullptr;
    emit projectChanged();
}