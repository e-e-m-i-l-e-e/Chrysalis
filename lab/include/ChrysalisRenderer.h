#ifndef CHRYSALIS_CHRYSALISRENDERER_H
#define CHRYSALIS_CHRYSALISRENDERER_H

#include <QQuickFramebufferObject>

#include "CartesianRenderer.h"
#include "ChrysalisOpenGLProgram.h"
#include "CursorRenderer.h"
#include "PatternRenderer.h"

class ChrysalisRenderer: public QQuickFramebufferObject::Renderer, QOpenGLFunctions {
public:
    explicit ChrysalisRenderer(ChrysalisOpenGLProgram* program,
                               CursorRenderer* cursorRenderer,
                               CartesianRenderer* cartesianRenderer);
    ~ChrysalisRenderer() override;

    void initialize();
    void changeCursor(QPointF&& cursor) const;
    void changeOffset(QPointF&& delta);
    void changeScale(double scalar, QPointF&& center);
protected:
    void render() override;
    void synchronize(QQuickFramebufferObject*) override;
    QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;
private:
    QRectF area_;
    double scale_ = 10.0;

    ChrysalisOpenGLProgram* program_;

    CursorRenderer* cursorRenderer_;
    CartesianRenderer* cartesianRenderer_;
    std::vector<PatternRenderer*> patternRenderers_;
};

#endif //CHRYSALIS_CHRYSALISRENDERER_H