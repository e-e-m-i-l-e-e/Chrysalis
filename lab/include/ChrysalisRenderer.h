#ifndef CHRYSALIS_CHRYSALISRENDERER_H
#define CHRYSALIS_CHRYSALISRENDERER_H

#include <QQuickFramebufferObject>

#include "ProjectRenderer.h"

class ChrysalisRenderer: public Chrysalis::ProjectRenderer, public QQuickFramebufferObject::Renderer {
public:
    explicit ChrysalisRenderer(Chrysalis::MainOpenGLProgram* program, Chrysalis::CartesianRenderer* cartesianRenderer);

    void changeCursor(QPointF&& cursor) const;
protected:
    void render() override;
    void synchronize(QQuickFramebufferObject*) override;
    QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;
};

#endif //CHRYSALIS_CHRYSALISRENDERER_H