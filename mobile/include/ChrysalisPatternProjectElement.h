#ifndef FASHIONDESIGNAPPS_CHRYSALISPATTERNPROJECTELEMENT_H
#define FASHIONDESIGNAPPS_CHRYSALISPATTERNPROJECTELEMENT_H

#include <QQuickItem>

#include "Archive.h"
#include "Project.h"

class ChrysalisPatternProjectElement: public QQuickItem {
    Q_OBJECT
    QML_NAMED_ELEMENT(ChrysalisPatternProject)

    Q_PROPERTY(bool hasProject READ hasProject NOTIFY projectChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QUrl filePath READ getFilePath WRITE setFilePath NOTIFY filePathChanged)
public:
    explicit ChrysalisPatternProjectElement(QQuickItem *parent = nullptr);
    ~ChrysalisPatternProjectElement() override;

    [[nodiscard]] QString getName() const;
    [[nodiscard]] QUrl getFilePath() const;
    [[nodiscard]] bool hasProject() const;

    void setName(const QString& name);
    void setFilePath(const QUrl& filePath);

    signals:
    void nameChanged();
    void projectChanged();
    void filePathChanged();

public slots:
    void createProject();
    void openProject(const QUrl& filePath);
    void saveProject(const QUrl& filePath);
    void closeProject();

private:
    QUrl filePath_;
    PB::Project* project = nullptr;
    Chrysalis::Pattern::Archive archive;
};

#endif //FASHIONDESIGNAPPS_CHRYSALISPATTERNPROJECTELEMENT_H