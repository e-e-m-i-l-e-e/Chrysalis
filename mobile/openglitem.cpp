#include "openglitem.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QQuickWindow>
#include <QDebug>

// ─────────────────────────────────────────────────────────────────────────────
//  GLSL shaders – written in GLSL ES 300 so the same source works on
//  desktop OpenGL (≥3.3) AND Android OpenGL ES 3.0.
//
//  Vertex layout (interleaved in one VBO):
//    location 0 → position  (vec3, 12 bytes)
//    location 1 → color     (vec3, 12 bytes)
//  One vertex = 24 bytes.
// ─────────────────────────────────────────────────────────────────────────────
static const char *vertexShaderSrc = R"(
#version 300 es

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

out vec3 vColor;   // passed to fragment shader

void main()
{
    vColor      = aColor;
    gl_Position = vec4(aPosition, 1.0);
}
)";

static const char *fragmentShaderSrc = R"(
#version 300 es
// NOTE: no "precision mediump float;" here.
// Qt injects "#define mediump" (empty) after #version on desktop, which turns
// "precision mediump float;" into "precision  float;" → syntax error.
// Removing it is safe: desktop GL ignores precision qualifiers entirely,
// and on Android/GLES Qt does NOT inject those defines, so GLES will use
// its default precision (mediump for fragment shaders in GLSL ES 300).

in  vec3 vColor;
out vec4 fragColor;

// Animated uniform: shifts the hue each frame
uniform float uColorOffset;

void main()
{
    // Rotate RGB channels by the offset so the triangle slowly cycles colour
    vec3 shifted = vec3(
        fract(vColor.r + uColorOffset),
        fract(vColor.g + uColorOffset + 0.333),
        fract(vColor.b + uColorOffset + 0.666)
    );
    fragColor = vec4(shifted, 1.0);
}
)";

// ─────────────────────────────────────────────────────────────────────────────
//  Triangle data  (NDC coordinates – no projection matrix needed for a demo)
//
//  Each row:  X      Y     Z      R     G     B
// ─────────────────────────────────────────────────────────────────────────────
static const GLfloat triangleVertices[] = {
//   position              color
     0.0f,  0.7f, 0.0f,   1.0f, 0.0f, 0.0f,  // top    – red
    -0.6f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // left   – green
     0.6f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // right  – blue
};

// ═════════════════════════════════════════════════════════════════════════════
//  OpenGLRenderer
// ═════════════════════════════════════════════════════════════════════════════

OpenGLRenderer::OpenGLRenderer()
    : m_vbo(QOpenGLBuffer::VertexBuffer)
{}

OpenGLRenderer::~OpenGLRenderer()
{
    // QOpenGLBuffer and QOpenGLVertexArrayObject clean themselves up
}

// Called once the first time render() runs (an OpenGL context is current)
void OpenGLRenderer::initialize()
{
    // Give QOpenGLFunctions access to the current context's function pointers
    initializeOpenGLFunctions();

    // ── Compile & link shaders ────────────────────────────────────────────────
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSrc))
        qFatal("Vertex shader error: %s", qPrintable(m_program.log()));

    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSrc))
        qFatal("Fragment shader error: %s", qPrintable(m_program.log()));

    if (!m_program.link())
        qFatal("Shader link error: %s", qPrintable(m_program.log()));

    m_uColorOffset = m_program.uniformLocation("uColorOffset");

    // ── Build VAO  ────────────────────────────────────────────────────────────
    // The VAO records every glVertexAttribPointer call made while it is bound.
    // When we bind the VAO again later, all those attribute settings are
    // restored automatically – no need to redo them every frame.
    m_vao.create();
    m_vao.bind();   // START recording

    // ── Upload vertex data into VBO ───────────────────────────────────────────
    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);   // data won't change
    m_vbo.allocate(triangleVertices, sizeof(triangleVertices));

    // ── Describe the layout (recorded by the VAO) ─────────────────────────────
    const int stride = 6 * sizeof(GLfloat);   // one vertex = 6 floats

    // Attribute 0 → position (3 floats, starting at byte 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                          // attribute location
        3,                          // components per vertex (x, y, z)
        GL_FLOAT,                   // data type
        GL_FALSE,                   // normalised?
        stride,                     // bytes between consecutive vertices
        reinterpret_cast<void*>(0)  // byte offset inside one vertex
    );

    // Attribute 1 → color (3 floats, starting at byte 12)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,                                    // attribute location
        3,                                    // r, g, b
        GL_FLOAT,
        GL_FALSE,
        stride,
        reinterpret_cast<void*>(3 * sizeof(GLfloat))  // skip 3 floats (position)
    );

    m_vao.release();   // STOP recording
    m_vbo.release();

    m_initialized = true;
    qDebug() << "OpenGL initialised. Renderer:" << (const char*)glGetString(GL_RENDERER);
}

// Called every frame by the render thread
void OpenGLRenderer::render()
{
    if (!m_initialized)
        initialize();

    // ── Clear ─────────────────────────────────────────────────────────────────
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);   // near-black background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ── Draw the triangle ─────────────────────────────────────────────────────
    m_program.bind();
    m_program.setUniformValue(m_uColorOffset, m_colorOffset);

    m_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);   // 3 vertices = 1 triangle
    m_vao.release();

    m_program.release();

    // Tell Qt we want another frame (drives the QML animation timer)
    update();
}

QOpenGLFramebufferObject *OpenGLRenderer::createFramebufferObject(const QSize &size)
{
    // A basic depth-enabled FBO that Qt will composite into the QML scene
    QOpenGLFramebufferObjectFormat fmt;
    fmt.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    fmt.setSamples(4);   // 4× MSAA – remove if your device doesn't support it
    return new QOpenGLFramebufferObject(size, fmt);
}

// Called by Qt before render() to copy main-thread data → render-thread data
void OpenGLRenderer::synchronize(QQuickFramebufferObject *baseItem)
{
    auto *item = static_cast<OpenGLItem *>(baseItem);
    m_colorOffset = item->m_colorOffset;
}

// ═════════════════════════════════════════════════════════════════════════════
//  OpenGLItem
// ═════════════════════════════════════════════════════════════════════════════

OpenGLItem::OpenGLItem(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
{
    // Redraw whenever the item's geometry changes (e.g. window resize)
    setMirrorVertically(true);  // FBO Y-axis matches QML's top-down convention
}

QQuickFramebufferObject::Renderer *OpenGLItem::createRenderer() const
{
    return new OpenGLRenderer();
}

void OpenGLItem::setColorOffset(float v)
{
    if (qFuzzyCompare(m_colorOffset, v))
        return;
    m_colorOffset = v;
    emit colorOffsetChanged();
    update();   // schedule a new render frame
}