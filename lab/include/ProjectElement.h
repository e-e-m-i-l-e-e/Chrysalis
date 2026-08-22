#ifndef CHRYSALIS_PROJECTELEMENT_H
#define CHRYSALIS_PROJECTELEMENT_H

#include "Project.h"
#include "ParametersElement.h"

namespace Chrysalis {
    class ProjectElement: public QQuickItem {
        Q_OBJECT
        QML_NAMED_ELEMENT(ChrysalisProject)

        Q_PROPERTY(bool hasProject READ hasProject NOTIFY projectChanged)
        Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QUrl filePath READ getFilePath WRITE setFilePath NOTIFY filePathChanged)
        Q_PROPERTY(ParametersElement* parameters READ getParameters WRITE setParameters NOTIFY parametersChanged)
    public:
        explicit ProjectElement(QQuickItem *parent = nullptr);

        [[nodiscard]] QString getName() const;
        [[nodiscard]] QUrl getFilePath() const;
        [[nodiscard]] bool hasProject() const;
        [[nodiscard]] ParametersElement* getParameters() const;

        void setName(const QString& name);
        void setFilePath(const QUrl& filePath);
        void setParameters(ParametersElement* parameters);

        signals:
        void nameChanged();
        void filePathChanged();
        void parametersChanged();
        void projectChanged(Project* project);

    public slots:
        void execute() const;
        void createProject();
        void openProject(const QUrl& filePath);
        void saveProject(const QUrl& filePath);
        void closeProject();
        void sendToCLO3D() const;

    private:
        QUrl filePath_;
        std::unique_ptr<Project> project_;
        ParametersElement* parameters_ = nullptr;
    };
}

#endif //CHRYSALIS_PROJECTELEMENT_H