#ifndef FASHIONDESIGNAPPS_PATTERNBUILDERSCENE_H
#define FASHIONDESIGNAPPS_PATTERNBUILDERSCENE_H

#include <QQuickFramebufferObject>

#include "ChrysalisRenderer.h"
#include "PatternBuilderRenderer.h"

class PatternBuilderSceneElement: public QQuickFramebufferObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(PatternBuilderScene)
public:
    explicit PatternBuilderSceneElement(QQuickItem *parent = nullptr);

    [[nodiscard]] Renderer* createRenderer() const override;

    QPointF& getMousePosition();
protected:
    void wheelEvent(QWheelEvent* event) override;
    void hoverMoveEvent(QHoverEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:
    ChrysalisRenderer* renderer_ = nullptr;
    bool isLeftMouseButtonPressed_ = false;
    QPointF mousePosition_;
    QPointF windowPosition_;
};

#endif //FASHIONDESIGNAPPS_PATTERNBUILDERSCENE_H