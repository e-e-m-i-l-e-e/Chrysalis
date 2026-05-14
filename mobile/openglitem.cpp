#include "openglitem.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QDebug>
#include <algorithm>

#include "Project.h"

// ─────────────────────────────────────────────────────────────────────────────
//  Shaders  (GLSL ES 300)
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
uniform vec4 uColor;
uniform bool uRound;
out vec4 fragColor;
void main() {
    if (uRound) {
        vec2 c = gl_PointCoord - 0.5;
        if (dot(c, c) > 0.25) discard;
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

    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Vertex,   vertSrc))
        qFatal("Vertex shader: %s",   qPrintable(m_program.log()));
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragSrc))
        qFatal("Fragment shader: %s", qPrintable(m_program.log()));
    if (!m_program.link())
        qFatal("Link: %s", qPrintable(m_program.log()));

    m_uColor     = m_program.uniformLocation("uColor");
    m_uRound     = m_program.uniformLocation("uRound");
    m_uPointSize = m_program.uniformLocation("uPointSize");

    glEnable(GL_PROGRAM_POINT_SIZE);

    m_vao.create();
    m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vbo.allocate(nullptr, 0);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                          2 * sizeof(GLfloat), nullptr);

    m_vao.release();
    m_vbo.release();

    m_initialized = true;
}

// Upload all three sets into ONE contiguous VBO region:
//   [ shape verts | edge verts | dot verts ]
void OpenGLRenderer::uploadVertices()
{
    // Build one flat buffer: [shape | loop0 | loop1 | ... | dots]
    QVector<GLfloat> data;

    // Shape
    m_shapeBatch = { 0, (int)m_shapeVerts.size() };
    for (const auto &p : m_shapeVerts) {
        data.append((GLfloat)p.x());
        data.append((GLfloat)p.y());
    }

    // Edge loops — one DrawBatch per loop
    m_edgeBatches.clear();
    for (const auto &loop : m_edgeLoops) {
        DrawBatch b { (int)(data.size() / 2), (int)loop.size() };
        m_edgeBatches.append(b);
        for (const auto &p : loop) {
            data.append((GLfloat)p.x());
            data.append((GLfloat)p.y());
        }
    }

    // Dots
    m_dotBatch = { (int)(data.size() / 2), (int)m_dotVerts.size() };
    for (const auto &p : m_dotVerts) {
        data.append((GLfloat)p.x());
        data.append((GLfloat)p.y());
    }

    m_vbo.bind();
    m_vbo.allocate(data.constData(), data.size() * sizeof(GLfloat));
    m_vbo.release();
}

void OpenGLRenderer::render()
{
    if (!m_initialized)
        initialize();

    if (m_dirty) {
        uploadVertices();
        m_dirty = false;
    }

    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(m_lineWidth);

    m_program.bind();
    m_vao.bind();

    auto setColor = [&](const QColor &c) {
        m_program.setUniformValue(m_uColor,
            (GLfloat)c.redF(), (GLfloat)c.greenF(),
            (GLfloat)c.blueF(), (GLfloat)c.alphaF());
    };

    // ── Pass 1: filled triangles (shape) ─────────────────────────────────────
    if (m_shapeBatch.count >= 3) {
        setColor(m_fillColor);
        m_program.setUniformValue(m_uRound,     false);
        m_program.setUniformValue(m_uPointSize, 1.0f);
        glDrawArrays(GL_TRIANGLES, m_shapeBatch.first, m_shapeBatch.count);
    }

    // ── Pass 2: outline + hole loops ─────────────────────────────────────────────
    if (!m_edgeBatches.isEmpty()) {
        setColor(m_edgeColor);
        m_program.setUniformValue(m_uRound,     false);
        m_program.setUniformValue(m_uPointSize, 1.0f);
        for (const DrawBatch &b : m_edgeBatches)
            if (b.count >= 2)
                glDrawArrays(GL_LINE_LOOP, b.first, b.count);
    }

    // ── Pass 3: individual dots ───────────────────────────────────────────────
    if (m_dotBatch.count >= 1) {
        setColor(m_dotColor);
        m_program.setUniformValue(m_uRound,     true);
        m_program.setUniformValue(m_uPointSize, m_pointSize);
        glDrawArrays(GL_POINTS, m_dotBatch.first, m_dotBatch.count);
    }

    m_vao.release();
    m_program.release();
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);
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
    auto *item = static_cast<OpenGLItem *>(baseItem);

    m_fillColor  = item->m_fillColor;
    m_edgeColor  = item->m_edgeColor;
    m_dotColor   = item->m_dotColor;
    m_lineWidth  = item->m_lineWidth;
    m_pointSize  = item->m_pointSize;

    // Compute a single world rect covering all point sets
    const QRectF rect = item->autoWorldRect();

    const QVector<QPointF> freshShape = item->toNdc(item->m_shapePoints, rect);
    const QVector<QPointF> freshDots  = item->toNdc(item->m_dotPoints,   rect);

    // Convert each loop independently
    QVector<QVector<QPointF>> freshLoops;
    freshLoops.reserve(item->m_edgeLoops.size());
    for (const auto &loop : item->m_edgeLoops) {
        QVariantList tmp;
        for (const auto &p : loop) tmp.append(p);
        freshLoops.append(item->toNdc(tmp, rect));
    }

    if (freshShape != m_shapeVerts || freshLoops != m_edgeLoops || freshDots != m_dotVerts) {
        m_shapeVerts = freshShape;
        m_edgeLoops  = freshLoops;
        m_dotVerts   = freshDots;
        m_dirty      = true;
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  OpenGLItem
// ═════════════════════════════════════════════════════════════════════════════

OpenGLItem::OpenGLItem(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
{
    setMirrorVertically(true);
    // ── Hardcoded pattern ─────────────────────────────────────────────────────
    // const auto pattern = (new Project())->addPattern("Test");
    //
    // pattern->addPoint("A",  0,  0);
    // pattern->addPoint("B",  0, 10);
    // pattern->addPoint("C", 10, 10);
    // pattern->addPoint("D", 10,  0);
    // pattern->addPoint("A1", 1,  1);
    // pattern->addPoint("B1", 1,  4);
    // pattern->addPoint("C1", 4,  4);
    // pattern->addPoint("D1", 4,  1);
    // pattern->addPoint("A2", 5,  6);
    // pattern->addPoint("B2", 5,  9);
    // pattern->addPoint("C2", 8,  9);
    // pattern->addPoint("D2", 8,  6);
    //
    // pattern->startOutline()
    //     .addPoint("A").addPoint("B").addPoint("C").addPoint("D");
    // pattern->startDart()
    //     .addPoint("A1").addPoint("B1").addPoint("C1").addPoint("D1").complete();
    // pattern->startDart()
    //     .addPoint("A2").addPoint("B2").addPoint("C2").addPoint("D2").complete();
    //
    // const auto shapeFlat = pattern->getShape();    // x,y,x,y,... triangles
    // const auto edgeFlat  = pattern->getOutline();  // x,y,x,y,... outline
    // const auto dotFlat   = pattern->getPoints();   // x,y,x,y,... named points
    //
    // // ── Convert flat float vectors → QVariantList<QPointF> ───────────────────
    // auto toVariantList = [](const auto &flat) {
    //     QVariantList out;
    //     out.reserve(flat.size() / 2);
    //     for (int i = 0; i + 1 < flat.size(); i += 2)
    //         out.append(QPointF(flat[i], flat[i + 1]));
    //     return out;
    // };
    //
    // m_shapePoints = toVariantList(shapeFlat);
    // m_dotPoints   = toVariantList(dotFlat);
    //
    // const std::vector<std::vector<float>> edgeLoopsFlat = pattern->getOutline();
    //
    // m_edgeLoops.clear();
    // for (const auto &loop : edgeLoopsFlat) {
    //     QVector<QPointF> pts;
    //     pts.reserve(loop.size() / 2);
    //     for (int i = 0; i + 1 < (int)loop.size(); i += 2)
    //         pts.append(QPointF(loop[i], loop[i + 1]));
    //     m_edgeLoops.append(pts);
    // }
}

QQuickFramebufferObject::Renderer *OpenGLItem::createRenderer() const
{
    return new OpenGLRenderer();
}

// ── NDC helpers ───────────────────────────────────────────────────────────────

// Returns the world-space bounding rect of ALL three point lists combined,
// or the explicit m_worldRect if one was set.
QRectF OpenGLItem::autoWorldRect() const
{
    if (m_worldRect.isValid())
        return m_worldRect;

    bool  hasAny = false;
    float minX =  1e30f, maxX = -1e30f;
    float minY =  1e30f, maxY = -1e30f;

    auto growPt = [&](float x, float y) {
        minX = std::min(minX, x); maxX = std::max(maxX, x);
        minY = std::min(minY, y); maxY = std::max(maxY, y);
        hasAny = true;
    };

    for (const auto &v : m_shapePoints) { auto p = v.toPointF(); growPt(p.x(), p.y()); }
    for (const auto &v : m_dotPoints)   { auto p = v.toPointF(); growPt(p.x(), p.y()); }
    for (const auto &loop : m_edgeLoops)
        for (const auto &p : loop) growPt(p.x(), p.y());   // ← was grow(m_edgePoints)

    if (!hasAny) return {};

    float padX = std::max((maxX - minX) * 0.1f, 0.5f);
    float padY = std::max((maxY - minY) * 0.1f, 0.5f);
    return QRectF(minX - padX, minY - padY,
                  (maxX - minX) + 2 * padX,
                  (maxY - minY) + 2 * padY);
}

QVector<QPointF> OpenGLItem::toNdc(const QVariantList &src, const QRectF &rect) const
{
    if (src.isEmpty() || !rect.isValid()) return {};

    QVector<QPointF> out;
    out.reserve(src.size());
    for (const auto &v : src) {
        QPointF p = v.toPointF();
        float nx =  2.0f * (p.x() - rect.left()) / rect.width()  - 1.0f;
        float ny =  2.0f * (p.y() - rect.top())  / rect.height() - 1.0f;
        out.append({ nx, ny });
    }
    return out;
}

// ── Setters ───────────────────────────────────────────────────────────────────

// Helper macro to reduce boilerplate
#define SETTER_IMPL(member, signal, type) \
    void OpenGLItem::set##signal(const type &v) { \
        if (member == v) return; \
        member = v; \
        emit signal##Changed(); \
        update(); \
    }

void OpenGLItem::setShapePoints(const QVariantList &v)
{
    if (m_shapePoints == v) return;
    m_shapePoints = v;
    emit shapePointsChanged();
    update();
}

void OpenGLItem::setDotPoints(const QVariantList &v)
{
    if (m_dotPoints == v) return;
    m_dotPoints = v;
    emit dotPointsChanged();
    update();
}

void OpenGLItem::setWorldRect(const QRectF &v)
{
    if (m_worldRect == v) return;
    m_worldRect = v;
    emit worldRectChanged();
    update();
}

void OpenGLItem::setFillColor(const QColor &v)
{
    if (m_fillColor == v) return;
    m_fillColor = v;
    emit fillColorChanged();
    update();
}

void OpenGLItem::setEdgeColor(const QColor &v)
{
    if (m_edgeColor == v) return;
    m_edgeColor = v;
    emit edgeColorChanged();
    update();
}

void OpenGLItem::setDotColor(const QColor &v)
{
    if (m_dotColor == v) return;
    m_dotColor = v;
    emit dotColorChanged();
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