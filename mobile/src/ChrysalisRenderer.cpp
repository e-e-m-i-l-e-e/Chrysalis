#include "ChrysalisRenderer.h"

#include <iostream>
#include <QOpenGLFramebufferObject>

#include "Logger.h"
#define LOGGER_NAME "Chrysalis Renderer"

void ChrysalisRenderer::initialize() {
    QOpenGLShader vertexShader {QOpenGLShader::Vertex};
    QOpenGLShader fragmentShader {QOpenGLShader::Fragment};

    if (!vertexShader.compileSourceFile(":/shaders/vertex.vert")) {
        LOG_CRITICAL("Failed to compile vertex shader. Error log: {}.", vertexShader.log().toStdString());
    }
    if (!fragmentShader.compileSourceFile(":/shaders/fragment.frag")) {
        LOG_CRITICAL("Failed to compile fragment shader. Error log: {}.", fragmentShader.log().toStdString());
    }
    if (!program_.addShader(&vertexShader)) {
        LOG_CRITICAL("Failed to add vertex shader. Error log: {}.", program_.log().toStdString());
    }
    if (!program_.addShader(&fragmentShader)) {
        LOG_CRITICAL("Failed to add fragment shader. Error log: {}.", program_.log().toStdString());
    }
    if (!program_.link()) {
        LOG_CRITICAL("Failed to link OpenGL program. Error log: {}.", program_.log().toStdString());
    }

    cartesianRenderer_.initialize();
}

QOpenGLFramebufferObject* ChrysalisRenderer::createFramebufferObject(const QSize& size) {
    area_.setSize(size);
    cartesianRenderer_.changeArea(area_);
    return Renderer::createFramebufferObject(size);
}

void ChrysalisRenderer::changeOffset(const QPointF& delta) {
    area_.setX(area_.x() - delta.x() / scale_);
    area_.setY(area_.y() - delta.y() / scale_);
    cartesianRenderer_.changeArea(area_);
}

void ChrysalisRenderer::changeScale(const double scalar, QPointF& center) {
    center.setY(center.y() - area_.height());
    const QPointF centerBefore = center / scale_;
    scale_ *= scalar;
    changeOffset(center - centerBefore * scale_);
}

void ChrysalisRenderer::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 projection;
    projection.ortho(
        0, framebufferObject()->width(),
        framebufferObject()->height(), 0,
        -1, 1
    );
    projection.scale(scale_);
    projection.translate(-area_.x(), area_.y(), 0);

    program_.bind();
    program_.setUniformValue("uProjection", projection);
    program_.setUniformValue("uColor", 1.f, 1.f, 1.f, 1.f);
    cartesianRenderer_.render();
    program_.release();
}
