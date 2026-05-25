#ifndef FASHIONDESIGNAPPS_CHRYSALISPATTERNPROJECTELEMENT_H
#define FASHIONDESIGNAPPS_CHRYSALISPATTERNPROJECTELEMENT_H

#include <QQuickItem>

#include "Archive.h"
#include "Project.h"

class ChrysalisPatternProjectElement: public QQuickItem {
    Q_OBJECT
    QML_NAMED_ELEMENT(ChrysalisPatternProject)
    Q_PROPERTY(bool hasProject READ hasProject NOTIFY projectChanged)
public:
    explicit ChrysalisPatternProjectElement(QQuickItem *parent = nullptr);
    ~ChrysalisPatternProjectElement() override;

    [[nodiscard]] bool hasProject() const;

    signals:
    void projectChanged();

public slots:
    void createProject();
    void openProject(const QUrl& filePath);
    void saveProject(const QUrl& filePath);
    void closeProject();

private:
    PB::Project* project = nullptr;
    Chrysalis::Pattern::Archive archive;
};

#endif //FASHIONDESIGNAPPS_CHRYSALISPATTERNPROJECTELEMENT_H