#ifndef FASHIONDESIGNAPPS_OPENGLITEM_H
#define FASHIONDESIGNAPPS_OPENGLITEM_H

#include <QQuickFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

// ─────────────────────────────────────────────────────────────────────────────
//  OpenGLRenderer
//  Lives on the render thread.  Does the actual OpenGL work.
// ─────────────────────────────────────────────────────────────────────────────
class OpenGLRenderer : public QQuickFramebufferObject::Renderer,
                       protected QOpenGLFunctions
{
public:
    OpenGLRenderer();
    ~OpenGLRenderer() override;

protected:
    // Called once per frame by Qt's scene-graph render thread
    void render() override;

    // Qt asks us to create the FBO it will composite into the QML scene
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

    // Called to sync data from the QML/main thread into the render thread
    void synchronize(QQuickFramebufferObject *item) override;

private:
    void initialize();          // one-time GL setup (shaders, VAO, VBO)

    bool                    m_initialized { false };

    // Shader program (vertex + fragment)
    QOpenGLShaderProgram    m_program;

    // GPU-side storage
    QOpenGLVertexArrayObject m_vao;   // records the vertex attribute layout
    QOpenGLBuffer            m_vbo;   // holds the raw vertex data

    // Uniform location (we animate a colour offset from QML)
    int m_uColorOffset { -1 };
    float m_colorOffset { 0.0f };     // value synced from the QML item
};


// ─────────────────────────────────────────────────────────────────────────────
//  OpenGLItem
//  The QML-visible type.  Lives on the main thread.
//  Expose it to QML with  QML_ELEMENT  so no manual qmlRegisterType() needed.
// ─────────────────────────────────────────────────────────────────────────────
class OpenGLItem : public QQuickFramebufferObject
{
    Q_OBJECT
    QML_ELEMENT  // makes "OpenGLItem { }" available in QML automatically

    // A simple animated property so we can see something move
    Q_PROPERTY(float colorOffset READ colorOffset WRITE setColorOffset NOTIFY colorOffsetChanged)

public:
    explicit OpenGLItem(QQuickItem *parent = nullptr);

    // Factory: Qt calls this on the render thread to create the renderer
    Renderer *createRenderer() const override;

    float colorOffset() const { return m_colorOffset; }
    void  setColorOffset(float v);

signals:
    void colorOffsetChanged();

private:
    float m_colorOffset { 0.0f };

    // Let the renderer read our data during synchronize()
    friend class OpenGLRenderer;
};

#endif //FASHIONDESIGNAPPS_OPENGLITEM_H