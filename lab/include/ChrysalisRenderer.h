#ifndef CHRYSALIS_CHRYSALISRENDERER_H
#define CHRYSALIS_CHRYSALISRENDERER_H

#include <QQuickFramebufferObject>

#include "CartesianRenderer.h"
#include "MainOpenGLProgram.h"
#include "CursorRenderer.h"
#include "PatternRenderer.h"
#include "Project.h"

class ChrysalisRenderer: public QQuickFramebufferObject::Renderer {
public:
    explicit ChrysalisRenderer(Chrysalis::MainOpenGLProgram* program,
                               CartesianRenderer* cartesianRenderer);
    ~ChrysalisRenderer() override;

    void initialize() const;
    void changeCursor(QPointF&& cursor) const;
    void changeOffset(QPointF&& delta);
    void changeScale(double scalar, QPointF&& center);
    void projectChanged(Chrysalis::Project* project);
protected:
    void render() override;
    void synchronize(QQuickFramebufferObject*) override;
    QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;
private:
    QRectF area_;
    double scale_ = 10.0;

    Chrysalis::MainOpenGLProgram* program_;

    CartesianRenderer* cartesianRenderer_;
    std::vector<PatternRenderer*> patternRenderers_;
};

#endif //CHRYSALIS_CHRYSALISRENDERER_H