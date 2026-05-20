#ifndef FASHIONDESIGNAPPS_CHRYSALISRENDERER_H
#define FASHIONDESIGNAPPS_CHRYSALISRENDERER_H

#include <QOpenGLShaderProgram>
#include <QQuickFramebufferObject>

#include "CartesianRenderer.h"

class ChrysalisRenderer: public QQuickFramebufferObject::Renderer {
public:
    void initialize();

    void changeOffset(const QPointF& delta);
    void changeScale(double scalar, QPointF& center);
protected:
    void render() override;
    QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;
private:
    QSize size_;
    QOpenGLShaderProgram program_;

    QRectF area_;
    double scale_ = 1.0;
    CartesianRenderer cartesianRenderer_;
};

#endif //FASHIONDESIGNAPPS_CHRYSALISRENDERER_H