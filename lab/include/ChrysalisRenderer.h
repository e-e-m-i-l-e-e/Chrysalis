#ifndef CHRYSALIS_CHRYSALISRENDERER_H
#define CHRYSALIS_CHRYSALISRENDERER_H

#include <QQuickFramebufferObject>

#include "ProjectRenderer.h"

class ChrysalisRenderer: public QQuickFramebufferObject::Renderer {
public:
    void initialize();
    void projectChanged(Chrysalis::Project* project);

    void changeCursor(QPointF&& cursor) const;
    void changeOffset(QPointF&& delta) const;
    void changeScale(double scalar, QPointF&& center) const;
protected:
    void render() override;
    void synchronize(QQuickFramebufferObject*) override;
    QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;
private:
    void changeSize() const;

    bool isInitialized_ = false;
    bool isProjectRendererInitialized_ = false;

    QSize size_;

    Chrysalis::Project* project_ = nullptr;
    Chrysalis::ProjectRenderer* projectRenderer_ = nullptr;
};

#endif //CHRYSALIS_CHRYSALISRENDERER_H