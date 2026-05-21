#include "PatternBuilderRenderer.h"

#include <iostream>
#include <QDirIterator>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLExtraFunctions>

#include "Logger.h"
#define LOGGER_NAME "PB Renderer"

#include <QOpenGLFramebufferObject>
#include <QQuickWindow>

#include "PatternBuilderSceneElement.h"
#include "Project.h"

auto project = PB::Project();
auto pattern1 = project.addPattern("Pattern 1");
auto spaceRendererData1 = pattern1.getSpaceRendererData();

auto pattern2 = project.addPattern("Pattern 2");
auto spaceRendererData2 = pattern2.getSpaceRendererData();

QOpenGLBuffer vboSpace1 {};
QOpenGLBuffer vboSpace2 {};
QOpenGLVertexArrayObject vaoSpace1 {};
QOpenGLVertexArrayObject vaoSpace2 {};

QOpenGLBuffer vboCartesian {};
QOpenGLVertexArrayObject vaoCartesian {};
std::vector<float> cartesian;

QPointF cursor;
QOpenGLBuffer vboCursor {};
QOpenGLVertexArrayObject vaoCursor {};
std::vector<float> cursorData;
bool displayCursor = false;

QElapsedTimer timer_;
qint64 lastFrameTime_ = 0;
float cursorAlpha_ = 0.0f;

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

    const auto layout = SpaceVertex::getLayout();
    vboSpace1.create();
    vboSpace1.bind();
    // vboSpace1.allocate(spaceRendererData1->getVBO().data(), spaceRendererData1->size());
    vaoSpace1.create();
    vaoSpace1.bind();
    for (int i = 0; i < layout.size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, layout[i].size, GL_FLOAT, GL_FALSE, sizeof(SpaceVertex), layout[i].offset);
    }
    vaoSpace1.release();
    vboSpace1.release();

    vboSpace2.create();
    vboSpace2.bind();
    // vboSpace2.allocate(spaceRendererData2->getVBO().data(), spaceRendererData2->size());
    vaoSpace2.create();
    vaoSpace2.bind();
    for (int i = 0; i < layout.size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, layout[i].size, GL_FLOAT, GL_FALSE, sizeof(SpaceVertex), layout[i].offset);
    }
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

    vboCursor.create();
    vboCursor.bind();
    vboCursor.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vaoCursor.create();
    vaoCursor.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SpaceVertex), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(SpaceVertex), reinterpret_cast<void*>(2 * sizeof(float)));   // skip x, y
    vaoCursor.release();
    vboCursor.release();

    timer_.start();
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
    projection.translate(offset_.x(), -offset_.y(), 0);

    // --- Delta time (always, not inside cursor block) ---
    const qint64 now = timer_.elapsed();
    const float dt = (now - lastFrameTime_) / 1000.0f;
    lastFrameTime_ = now;

    const float duration = 0.3f;
    if (displayCursor) cursorAlpha_ = std::min(1.0f, cursorAlpha_ + dt / duration);
    else cursorAlpha_ = std::max(0.0f, cursorAlpha_ - dt / duration);

    // --- Cartesian grid ---
    cartesian.clear();
    const int xFrom = static_cast<int>(std::floor(-offset_.x() / 10) * 10);
    const int xRange = static_cast<int>(std::ceil(static_cast<float>(framebufferObject()->width()) / scale_ / 10.0) * 10) + 10;
    const int yFrom = static_cast<int>(std::floor(offset_.y() / 10) * 10);
    const int yRange = static_cast<int>(std::ceil(static_cast<float>(framebufferObject()->height()) / scale_ / 10.0) * 10) + 10;
    cartesian.push_back(0);
    cartesian.push_back(yFrom);
    cartesian.push_back(0);
    cartesian.push_back(yFrom + yRange);
    cartesian.push_back(xFrom);
    cartesian.push_back(0);
    cartesian.push_back(xFrom + xRange);
    cartesian.push_back(0);
    for (int i = 0; i <= xRange; i += 10) {
        cartesian.push_back(xFrom + i);
        cartesian.push_back(yFrom);
        cartesian.push_back(xFrom + i);
        cartesian.push_back(yFrom + yRange);
    }
    for (int i = 0; i <= yRange; i += 10) {
        cartesian.push_back(xFrom);
        cartesian.push_back(yFrom + i);
        cartesian.push_back(xFrom + xRange);
        cartesian.push_back(yFrom + i);
    }

    vboCartesian.bind();
    vboCartesian.allocate(cartesian.data(), cartesian.size() * sizeof(float));
    vaoCartesian.release();

    // --- Update cursor buffer only when a point is snapped ---
    if (displayCursor) {
        cursorData.clear();
        cursorData.push_back(cursor.x());
        cursorData.push_back(0);
        cursorData.push_back(0);

        cursorData.push_back(cursor.x());
        cursorData.push_back(cursor.y());
        cursorData.push_back(cursor.y());

        cursorData.push_back(0);
        cursorData.push_back(cursor.y());
        cursorData.push_back(0);

        cursorData.push_back(cursor.x());
        cursorData.push_back(cursor.y());
        cursorData.push_back(cursor.x());

        vboCursor.bind();
        vboCursor.allocate(cursorData.data(), cursorData.size() * sizeof(float));
        vboCursor.release();
    }

    // --- Draw ---
    program_.bind();
    program_.setUniformValue("uProjection", projection);

    vaoCartesian.bind();
    program_.setUniformValue("uColor", 1.f, 1.f, 1.f, 1.f);
    glDrawArrays(GL_LINES, 0, 4);
    program_.setUniformValue("uColor", 1.f, 1.f, 1.f, 0.1f);
    glDrawArrays(GL_LINES, 4, cartesian.size() / 2 - 4);
    vaoCartesian.release();

    program_.setUniformValue("uColor", 1.f, 0.f, 0.f, 1.f);
    glPointSize(0.5f * scale_);

    vaoSpace1.bind();
    // glDrawArrays(GL_LINES, spaceRendererData1->linesRange().from, spaceRendererData1->linesRange().count);
    for (size_t i = spaceRendererData1->arrowsRange().from; i <= spaceRendererData1->arrowsRange().from + spaceRendererData1->arrowsRange().count; i += 4) {
        glDrawArrays(GL_TRIANGLE_STRIP, i, 4);
    }
    program_.setUniformValue("uIsPoint", true);
    glDrawArrays(GL_POINTS, spaceRendererData1->pointsRange().from, spaceRendererData1->pointsRange().count);
    program_.setUniformValue("uIsPoint", false);
    vaoSpace1.release();

    vaoSpace2.bind();
    // glDrawArrays(GL_LINES, spaceRendererData2->linesRange().from, spaceRendererData2->linesRange().count);
    for (size_t i = spaceRendererData2->arrowsRange().from; i <= spaceRendererData2->arrowsRange().from + spaceRendererData2->arrowsRange().count; i += 4) {
        glDrawArrays(GL_TRIANGLE_STRIP, i, 4);
    }
    program_.setUniformValue("uIsPoint", true);
    glDrawArrays(GL_POINTS, spaceRendererData2->pointsRange().from, spaceRendererData2->pointsRange().count);
    program_.setUniformValue("uIsPoint", false);
    vaoSpace2.release();

    // Draw cursor whenever alpha > 0 (covers both fade-in and fade-out)
    if (cursorAlpha_ > 0.0f) {
        vaoCursor.bind();
        program_.setUniformValue("uColor", 0.f, 1.f, 0.f, cursorAlpha_);
        glDrawArrays(GL_LINES, 0, static_cast<int>(cursorData.size() / 3));
        vaoCursor.release();
    }

    program_.release();
    size_ = framebufferObject()->size();
}

void PatternBuilderRenderer::synchronize(QQuickFramebufferObject* object) {
    // position_.first = position_.second;
    // position_.second = object->window()->position();
    //
    // displayCursor = false;
    // auto cursor1 = dynamic_cast<PatternBuilderSceneElement*>(object)->getMousePosition() * object->window()->devicePixelRatio();
    // cursor1.setX(cursor1.x() / scale_ - offset_.x());
    // cursor1.setY(object->height() * object->window()->devicePixelRatio() / scale_ - cursor1.y() / scale_ + offset_.y());
    //
    // std::vector<SpaceVertex> vertices = spaceRendererData1->getVBO();
    // std::vector<SpaceVertex> pattern2Vbo = spaceRendererData2->getVBO();
    // vertices.insert(vertices.end(), pattern2Vbo.begin(), pattern2Vbo.end());
    //
    // for (auto& vertex : vertices) {
    //     float distance = sqrt(pow(vertex.x() - cursor1.x(), 2) + pow(vertex.y() - cursor1.y(), 2));
    //     if (distance <= 0.25f) {
    //         cursor = {vertex.x(), vertex.y()};
    //         displayCursor = true;
    //         break; // use break instead of return so update() below always runs
    //     }
    // }
    //
    // // Keep rendering while fading in or out
    // if (displayCursor || cursorAlpha_ > 0.0f)
    //     object->update();
}

void PatternBuilderRenderer::changeOffset(const float offsetX, const float offsetY) {
    offset_ += {offsetX / scale_, offsetY / scale_};
    std::cout << "Offset x = " << offset_.x() << " offset y = " << offset_.y() << " width = " << framebufferObject()->width() / scale_ << " height = " << framebufferObject()->height() / scale_ << std::endl;
}

void PatternBuilderRenderer::changeScale(const float scale, const QPointF& scalePoint) {
    const double x = scalePoint.x() / scale_ - offset_.x();
    const double y = (framebufferObject()->height() - scalePoint.y()) / scale_ + offset_.y();

    scale_ *= scale;

    offset_.setX(scalePoint.x() / scale_ - x);
    offset_.setY(y - (framebufferObject()->height() - scalePoint.y()) / scale_);
    std::cout << "Offset x = " << offset_.x() << " offset y = " << offset_.y() << " width = " << framebufferObject()->width() / scale_ << " height = " << framebufferObject()->height() / scale_ << std::endl;
}
