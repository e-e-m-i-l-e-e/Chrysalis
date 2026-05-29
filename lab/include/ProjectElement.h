#ifndef CHRYSALIS_PROJECTELEMENT_H
#define CHRYSALIS_PROJECTELEMENT_H

#include <QQuickItem>

#include "Project.h"
#include "ParametersModel.h"

namespace Chrysalis {
    class ProjectElement: public QQuickItem {
        Q_OBJECT
        QML_NAMED_ELEMENT(ChrysalisProject)

        Q_PROPERTY(bool hasProject READ hasProject NOTIFY projectChanged)
        Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QUrl filePath READ getFilePath WRITE setFilePath NOTIFY filePathChanged)
        Q_PROPERTY(ParametersModel* parameters READ getParameters WRITE setParameters NOTIFY parametersChanged)
    public:
        explicit ProjectElement(QQuickItem *parent = nullptr);
        ~ProjectElement() override;

        [[nodiscard]] QString getName() const;
        [[nodiscard]] QUrl getFilePath() const;
        [[nodiscard]] bool hasProject() const;
        [[nodiscard]] ParametersModel* getParameters() const;

        void setName(const QString& name);
        void setFilePath(const QUrl& filePath);
        void setParameters(ParametersModel* parameters);

        signals:
        void nameChanged();
        void projectChanged();
        void filePathChanged();
        void parametersChanged();

    public slots:
        void createProject();
        void openProject(const QUrl& filePath);
        void saveProject(const QUrl& filePath);
        void closeProject();

    private:
        QUrl filePath_;
        Project* project = nullptr;
        ParametersModel* parameters_ = nullptr;
    };
}

#endif //CHRYSALIS_PROJECTELEMENT_H