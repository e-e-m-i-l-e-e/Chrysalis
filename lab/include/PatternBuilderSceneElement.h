#ifndef CHRYSALIS_PATTERNBUILDERSCENE_H
#define CHRYSALIS_PATTERNBUILDERSCENE_H

#include <QQuickFramebufferObject>

#include "Project.h"
#include "ChrysalisRenderer.h"

class PatternBuilderSceneElement: public QQuickFramebufferObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(PatternBuilderScene)
public:
    explicit PatternBuilderSceneElement(QQuickItem *parent = nullptr);

    [[nodiscard]] Renderer* createRenderer() const override;
public slots:
    void projectChanged(Chrysalis::Project* project);
protected:
    void wheelEvent(QWheelEvent* event) override;
    void hoverMoveEvent(QHoverEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:
    QPointF normalize(QPointF&& point) const;

    ChrysalisRenderer* renderer_ = nullptr;
    bool isLeftMouseButtonPressed_ = false;
    QPointF mousePosition_;
    QPointF windowPosition_;
};

#endif //CHRYSALIS_PATTERNBUILDERSCENE_H