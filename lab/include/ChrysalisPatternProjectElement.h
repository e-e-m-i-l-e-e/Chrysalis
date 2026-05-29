#ifndef FASHIONDESIGNAPPS_CHRYSALISPATTERNPROJECTELEMENT_H
#define FASHIONDESIGNAPPS_CHRYSALISPATTERNPROJECTELEMENT_H

#include <QQuickItem>

#include "Archive.h"
#include "PatternParametersModel.h"
#include "Project.h"

class ChrysalisPatternProjectElement: public QQuickItem {
    Q_OBJECT
    QML_NAMED_ELEMENT(ChrysalisPatternProject)

    Q_PROPERTY(bool hasProject READ hasProject NOTIFY projectChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QUrl filePath READ getFilePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(PatternParametersModel* parameters READ getParameters WRITE setParameters NOTIFY parametersChanged)
public:
    explicit ChrysalisPatternProjectElement(QQuickItem *parent = nullptr);
    ~ChrysalisPatternProjectElement() override;

    [[nodiscard]] QString getName() const;
    [[nodiscard]] QUrl getFilePath() const;
    [[nodiscard]] bool hasProject() const;
    PatternParametersModel* getParameters() const;

    void setName(const QString& name);
    void setFilePath(const QUrl& filePath);
    void setParameters(PatternParametersModel* parameters);

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
    Chrysalis::Project* project = nullptr;
    Chrysalis::Archive archive;
    PatternParametersModel* parameters_ = nullptr;
};

#endif //FASHIONDESIGNAPPS_CHRYSALISPATTERNPROJECTELEMENT_H