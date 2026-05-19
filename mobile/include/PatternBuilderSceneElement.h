#ifndef FASHIONDESIGNAPPS_PATTERNBUILDERSCENE_H
#define FASHIONDESIGNAPPS_PATTERNBUILDERSCENE_H

#include <QQuickFramebufferObject>

#include "PatternBuilderRenderer.h"

class PatternBuilderSceneElement: public QQuickFramebufferObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(PatternBuilderScene)
public:
    explicit PatternBuilderSceneElement(QQuickItem *parent = nullptr);

    [[nodiscard]] Renderer* createRenderer() const override;

    QPointF& getMousePosition();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void hoverMoveEvent(QHoverEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    PatternBuilderRenderer* renderer_ = nullptr;
    bool isMousePressed_ = false;
    QPointF mousePosition_;
};

#endif //FASHIONDESIGNAPPS_PATTERNBUILDERSCENE_H