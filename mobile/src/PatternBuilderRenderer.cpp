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

    vboCartesian.create();
    vboCartesian.bind();
    vboCartesian.setUsagePattern(QOpenGLBuffer::DynamicDraw);
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

    if (position_.first.x() != position_.second.x()) offset_.setX(offset_.x() + (framebufferObject()->width() - size_.width()) / scale_);
    if (position_.first.y() == position_.second.y()) offset_.setY(offset_.y() - (framebufferObject()->height() - size_.height()) / scale_);

    QMatrix4x4 projection;

    projection.ortho(0, framebufferObject()->width(), framebufferObject()->height(), 0, -1, 1);
    projection.scale(scale_);
    std::cout
        << "\n\nx = " << offset_.x() << " y = " << offset_.y()
        << " count x = " << framebufferObject()->width() / scale_
        << " count y = " << framebufferObject()->height() / scale_ << std::endl;
    projection.translate(offset_.x(), -offset_.y(), 0);

    cartesian.clear();
    const int xFrom = -static_cast<int>(offset_.x() / 10) * 10 - 20;
    const int xRange = framebufferObject()->width() / scale_ + 20;
    const int yFrom = static_cast<int>(offset_.y() / 10) * 10 - 20;
    const int yRange = framebufferObject()->height() / scale_ + 20;
    cartesian.push_back(0);
    cartesian.push_back(yFrom);
    cartesian.push_back(0);
    cartesian.push_back(yFrom + yRange);
    cartesian.push_back(xFrom);
    cartesian.push_back(0);
    cartesian.push_back(xFrom + xRange);
    cartesian.push_back(0);
    std::cout << "Cartesian x = ";
    for (int i = 0; i <= xRange; i += 10) {
        cartesian.push_back(xFrom + i);
        cartesian.push_back(yFrom);
        cartesian.push_back(xFrom + i);
        cartesian.push_back(yFrom + yRange);
        std::cout << i << " ";
    }
    std::cout << "\nCartesian y = ";
    for (int i = 0; i <= yRange; i += 10) {
        cartesian.push_back(xFrom);
        cartesian.push_back(yFrom + i);
        cartesian.push_back(xFrom + xRange);
        cartesian.push_back(yFrom + i);
        std::cout << i << " ";
    }

    vboCartesian.bind();
    vboCartesian.allocate(cartesian.data(), cartesian.size() * sizeof(float));
    vaoCartesian.release();

    program_.bind();
    program_.setUniformValue("uProjection", projection);


    vaoCartesian.bind();
    program_.setUniformValue("uColor", 1.f, 1.f, 1.f, 1.f);
    glDrawArrays(GL_LINES, 0, 4);
    program_.setUniformValue("uColor", 1.f, 1.f, 1.f, 0.1f);
    glDrawArrays(GL_LINES, 4, cartesian.size() / 2 - 4);
    vaoCartesian.release();

    program_.setUniformValue("uColor", 1.f, 0.f, 0.f, 1.f);

    vaoSpace1.bind();
    glDrawArrays(GL_LINE_LOOP, 0, pattern1.getVBO().size());
    vaoSpace1.release();

    vaoSpace2.bind();
    glDrawArrays(GL_LINE_LOOP, 0, pattern2.getVBO().size());
    vaoSpace2.release();

    program_.release();
    size_ = framebufferObject()->size();
}

void PatternBuilderRenderer::synchronize(QQuickFramebufferObject* object) {
    position_.first = position_.second;
    position_.second = object->window()->position();
}

void PatternBuilderRenderer::changeOffset(const float offsetX, const float offsetY) {
    offset_ += {offsetX / scale_, offsetY / scale_};
}

void PatternBuilderRenderer::changeScale(const float scale, const QPointF& scalePoint) {
    const float x = scalePoint.x() / scale_ - offset_.x();
    const float y = (framebufferObject()->height() - scalePoint.y()) / scale_ + offset_.y();

    scale_ *= scale;

    offset_.setX(scalePoint.x() / scale_ - x);
    offset_.setY(y - (framebufferObject()->height() - scalePoint.y()) / scale_);
}
