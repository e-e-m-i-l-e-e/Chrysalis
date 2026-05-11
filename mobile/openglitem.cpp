#include "openglitem.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QDebug>
#include <algorithm>

#include "Project.h"

// ─────────────────────────────────────────────────────────────────────────────
//  Shaders  (GLSL ES 300 — works on desktop ≥3.3 and Android ES 3.0)
// ─────────────────────────────────────────────────────────────────────────────
static const char *vertSrc = R"(
#version 300 es
layout(location = 0) in vec2 aPosition;
uniform float uPointSize;

void main() {
    gl_PointSize = uPointSize;
    gl_Position  = vec4(aPosition, 0.0, 1.0);
}
)";

static const char *fragSrc = R"(
#version 300 es
uniform vec4  uColor;
uniform bool  uRound;     // true when drawing points
out vec4 fragColor;

void main() {
    if (uRound) {
        // gl_PointCoord is [0,1] across the point sprite
        vec2 c = gl_PointCoord - 0.5;
        if (dot(c, c) > 0.25)   // outside unit circle
            discard;
    }
    fragColor = uColor;
}
)";

// ═════════════════════════════════════════════════════════════════════════════
//  OpenGLRenderer
// ═════════════════════════════════════════════════════════════════════════════

OpenGLRenderer::OpenGLRenderer()
    : m_vbo(QOpenGLBuffer::VertexBuffer)
{}

OpenGLRenderer::~OpenGLRenderer() {}

void OpenGLRenderer::initialize()
{
    initializeOpenGLFunctions();

    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertSrc))
        qFatal("Vertex shader: %s", qPrintable(m_program.log()));
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragSrc))
        qFatal("Fragment shader: %s", qPrintable(m_program.log()));
    if (!m_program.link())
        qFatal("Link: %s", qPrintable(m_program.log()));

    m_uColor     = m_program.uniformLocation("uColor");
    m_uRound     = m_program.uniformLocation("uRound");
    m_uPointSize = m_program.uniformLocation("uPointSize");

    // Required to use gl_PointSize in the vertex shader
    glEnable(GL_PROGRAM_POINT_SIZE);

    m_vao.create();
    m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    // DynamicDraw → polygon can change at runtime
    m_vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vbo.allocate(nullptr, 0);   // empty for now

    // layout: vec2 position only, stride = 8 bytes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                          2 * sizeof(GLfloat), nullptr);

    m_vao.release();
    m_vbo.release();

    m_initialized = true;
}

void OpenGLRenderer::uploadVertices()
{
    m_vertexCount = m_points.size();
    if (m_vertexCount == 0) return;

    QVector<GLfloat> data;
    data.reserve(m_vertexCount * 2);
    for (const auto &p : m_points) {
        data.append(static_cast<GLfloat>(p.x()));
        data.append(static_cast<GLfloat>(p.y()));
    }

    m_vbo.bind();
    m_vbo.allocate(data.constData(), data.size() * sizeof(GLfloat));
    m_vbo.release();
}

void OpenGLRenderer::render()
{
    if (!m_initialized)
        initialize();

    if (m_dirty) {               // ← flush here, context is guaranteed active
        uploadVertices();
        m_dirty = false;
    }

    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_vertexCount < 2) return;

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(m_lineWidth);

    m_program.bind();
    m_program.setUniformValue(m_uColor,
        (GLfloat)m_lineColor.redF(),   (GLfloat)m_lineColor.greenF(),
        (GLfloat)m_lineColor.blueF(),  (GLfloat)m_lineColor.alphaF());

    m_vao.bind();

    // ── Pass 1: outline ───────────────────────────────────────────
    m_program.setUniformValue(m_uRound,     false);
    m_program.setUniformValue(m_uPointSize, 1.0f);   // ignored for lines
    glDrawArrays(GL_LINE_LOOP, 0, m_vertexCount);

    // ── Pass 2: vertex dots ───────────────────────────────────────
    m_program.setUniformValue(m_uRound,     true);
    m_program.setUniformValue(m_uPointSize, m_pointSize);
    glDrawArrays(GL_POINTS, 0, m_vertexCount);        // same VAO, same data

    m_vao.release();
    m_program.release();
    glDisable(GL_LINE_SMOOTH);
}

QOpenGLFramebufferObject *OpenGLRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat fmt;
    fmt.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    fmt.setSamples(4);
    return new QOpenGLFramebufferObject(size, fmt);
}

void OpenGLRenderer::synchronize(QQuickFramebufferObject *baseItem)
{
    auto *item    = static_cast<OpenGLItem *>(baseItem);
    m_lineColor   = item->m_lineColor;
    m_lineWidth   = item->m_lineWidth;
    m_pointSize   = item->m_pointSize;   // ← was missing

    QVector<QPointF> fresh = item->ndcPoints();
    if (fresh != m_points) {
        m_points = fresh;
        m_dirty  = true;
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  OpenGLItem
// ═════════════════════════════════════════════════════════════════════════════

OpenGLItem::OpenGLItem(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
{
    setMirrorVertically(true);
}

QQuickFramebufferObject::Renderer *OpenGLItem::createRenderer() const
{
    return new OpenGLRenderer();
}

// ── NDC conversion ────────────────────────────────────────────────────────────
QVector<QPointF> OpenGLItem::ndcPoints() const
{
    if (m_points.isEmpty()) return {};

    // Collect world-space points from QVariantList
    QVector<QPointF> world;
    world.reserve(m_points.size());
    for (const auto &v : m_points) {
        QPointF p = v.toPointF();
        world.append(p);
    }

    // Determine mapping rect (explicit or auto-fit with 10 % padding)
    QRectF rect = m_worldRect;
    if (!rect.isValid()) {
        float minX = world[0].x(), maxX = minX;
        float minY = world[0].y(), maxY = minY;
        for (const auto &p : world) {
            minX = std::min(minX, (float)p.x());
            maxX = std::max(maxX, (float)p.x());
            minY = std::min(minY, (float)p.y());
            maxY = std::max(maxY, (float)p.y());
        }
        float padX = (maxX - minX) * 0.1f;
        float padY = (maxY - minY) * 0.1f;
        rect = QRectF(minX - padX, minY - padY,
                      (maxX - minX) + 2 * padX,
                      (maxY - minY) + 2 * padY);
    }

    // Map world → NDC [-1, 1]
    QVector<QPointF> ndc;
    ndc.reserve(world.size());
    for (const auto &p : world) {
        float nx =  2.0f * (p.x() - rect.left())  / rect.width()  - 1.0f;
        float ny =  2.0f * (p.y() - rect.top())   / rect.height() - 1.0f;
        ndc.append({ nx, ny });
    }
    return ndc;
}

// ── Property setters ──────────────────────────────────────────────────────────
void OpenGLItem::setPoints(const QVariantList &v)
{
    if (m_points == v) return;

    const auto pattern = (new Project())->addPattern("Test");
    pattern->addPoint("A", 0, 0);
    pattern->addPoint("B", 0, 10);
    pattern->addPoint("C", 10, 10);
    pattern->addPoint("D", 10, 0);
    pattern->startOutline().addPoint("A").addPoint("C").addPoint("B").addPoint("D");
    pattern->startDart().addPoint("A").addPoint("B").addPoint("D");
    const auto points = pattern->getOutline();

    QVariantList newPoints;
    for (int i = 0; i < points.size(); i += 2) {
        newPoints.append(QPointF(points[i], points[i + 1]));
    }
    m_points = newPoints;
    emit pointsChanged();
    update();
}

void OpenGLItem::setWorldRect(const QRectF &v)
{
    if (m_worldRect == v) return;
    m_worldRect = v;
    emit worldRectChanged();
    update();
}

void OpenGLItem::setLineColor(const QColor &v)
{
    if (m_lineColor == v) return;
    m_lineColor = v;
    emit lineColorChanged();
    update();
}

void OpenGLItem::setLineWidth(float v)
{
    if (qFuzzyCompare(m_lineWidth, v)) return;
    m_lineWidth = v;
    emit lineWidthChanged();
    update();
}

void OpenGLItem::setPointSize(float v)
{
    if (qFuzzyCompare(m_pointSize, v)) return;
    m_pointSize = v;
    emit pointSizeChanged();
    update();
}