#ifndef FASHIONDESIGNAPPS_OPENGLRENDERER_H
#define FASHIONDESIGNAPPS_OPENGLRENDERER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuickFramebufferObject>

class PatternBuilderRenderer: public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions {
public:
    void initialize();
    void changeOffset(float offsetX, float offsetY);
    void changeScale(float scale, const QPointF& scalePoint);
    void changeGeometry(const QRectF& geometry);
protected:
    void render() override;
private:
    QOpenGLShaderProgram program_;
    QVector2D offset_ = {0, 0};
    float scale_ = 10;
    QRectF geometry_;
};

#endif //FASHIONDESIGNAPPS_OPENGLRENDERER_H