#include "PatternBuilderRenderer.h"

#include <iostream>
#include <QDirIterator>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "Logger.h"
#define LOGGER_NAME "PB Renderer"

#include <QOpenGLFramebufferObject>
#include <QQuickWindow>

#include "PatternBuilderSceneElement.h"
#include "Project.h"

auto project = PB::Project();
auto pattern1 = project.addPattern("Pattern 1");
auto pattern2 = project.addPattern("Pattern 2");

QOpenGLBuffer vboSpace1 {};
QOpenGLBuffer vboSpace2 {};
QOpenGLVertexArrayObject vaoSpace1 {};
QOpenGLVertexArrayObject vaoSpace2 {};

QOpenGLBuffer vboCartesian {};
QOpenGLVertexArrayObject vaoCartesian {};
std::vector<float> cartesian;

int uColor;

void PatternBuilderRenderer::initialize() {
    initializeOpenGLFunctions();

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

    pattern1
        .addPoint("A", 0, 0)
        .nextPoint("B", Space::Direction::UP, 10)
        .addPoint("C", 10, 10)
        .nextPoint("D", Space::Direction::DOWN, 10);

    pattern2
        .addPoint("A", 7, 5)
        .nextPoint("B", Space::Direction::UP, 20)
        .nextPoint("C", Space::Direction::RIGHT, 5)
        .nextPoint("D", Space::Direction::DOWN, 7)
        .nextPoint("E", Space::Direction::RIGHT, 10)
        .nextPoint("F", Space::Direction::DOWN, 10);

    vboSpace1.create();
    vboSpace1.bind();
    vboSpace1.allocate(pattern1.getVBO().data(), pattern1.getVBO().size() * sizeof(SpaceVertex));
    vaoSpace1.create();
    vaoSpace1.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SpaceVertex), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(SpaceVertex), reinterpret_cast<void*>(2 * sizeof(float)));   // skip x, y
    vaoSpace1.release();
    vboSpace1.release();

    vboSpace2.create();
    vboSpace2.bind();
    vboSpace2.allocate(pattern2.getVBO().data(), pattern2.getVBO().size() * sizeof(SpaceVertex));
    vaoSpace2.create();
    vaoSpace2.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SpaceVertex), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(SpaceVertex), reinterpret_cast<void*>(2 * sizeof(float)));   // skip x, y
    vaoSpace2.release();
    vboSpace2.release();

    for (int i = -100; i <= 100; i += 10) {
        cartesian.push_back(i);
        cartesian.push_back(-100);
        cartesian.push_back(i);
        cartesian.push_back(100);
        cartesian.push_back(-100);
        cartesian.push_back(i);
        cartesian.push_back(100);
        cartesian.push_back(i);
    }
    vboCartesian.create();
    vboCartesian.bind();
    vboCartesian.allocate(cartesian.data(), cartesian.size() * sizeof(float));
    vaoCartesian.create();
    vaoCartesian.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    vaoCartesian.release();
    vboCartesian.release();
}

void PatternBuilderRenderer::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    std::cout << "Framebuffer " << framebufferObject()->width() << " " << framebufferObject()->height() << std::endl;
    QMatrix4x4 projection;
    projection.ortho(
        offset_.x(), geometry_.width() / scale_ + offset_.x(),
        geometry_.height() / scale_ + offset_.y(), offset_.y(),
        -1.0f, 1.0f
    );

    program_.bind();
    program_.setUniformValue("uProjection", projection);
    program_.setUniformValue("uColor", 1.f, 1.f, 1.f, 0.1f);

    vaoCartesian.bind();
    glDrawArrays(GL_LINES, 0, cartesian.size() / 2);
    vaoCartesian.release();

    program_.setUniformValue("uColor", 1.f, 0.f, 0.f, 1.f);

    vaoSpace1.bind();
    glDrawArrays(GL_LINE_LOOP, 0, pattern1.getVBO().size());
    vaoSpace1.release();

    vaoSpace2.bind();
    glDrawArrays(GL_LINE_LOOP, 0, pattern2.getVBO().size());
    vaoSpace2.release();

    program_.release();
}

void PatternBuilderRenderer::changeOffset(const float offsetX, const float offsetY) {
    offset_ -= {offsetX / scale_, -offsetY / scale_};
}

void PatternBuilderRenderer::changeScale(const float scale, const QPointF& scalePoint) {
    const float x = offset_.x() + scalePoint.x() / scale_;
    const float y = offset_.y() + (geometry_.height() - scalePoint.y()) / scale_;

    scale_ *= scale;

    offset_.setX(x - scalePoint.x() / scale_);
    offset_.setY(y - (geometry_.height() - scalePoint.y()) / scale_);
}

void PatternBuilderRenderer::changeGeometry(const QRectF& geometry) {
    std::cout << "Change geometry " << geometry.width() << " " << geometry.height() << std::endl;
    if (geometry.x() != geometry_.x()) offset_.setX(offset_.x() - (geometry.width() - geometry_.width()) / scale_);
    if (geometry.y() == geometry_.y()) offset_.setY(offset_.y() - (geometry.height() - geometry_.height()) / scale_);
    geometry_ = geometry;
}
