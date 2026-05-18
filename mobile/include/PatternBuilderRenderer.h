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
protected:
    void render() override;
    void synchronize(QQuickFramebufferObject*) override;
private:
    QOpenGLShaderProgram program_;
    QVector2D offset_ = {-99, -1};
    float scale_ = 10;

    QSize size_;
    std::pair<QPointF, QPointF> position_; // <prev, current>
};

#endif //FASHIONDESIGNAPPS_OPENGLRENDERER_H