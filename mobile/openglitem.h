#pragma once

#include <QQuickFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QVariantList>
#include <QColor>
#include <QRectF>

class OpenGLItem;

// ─────────────────────────────────────────────────────────────────────────────
//  Renderer
// ─────────────────────────────────────────────────────────────────────────────
class OpenGLRenderer : public QQuickFramebufferObject::Renderer,
                       protected QOpenGLFunctions
{
public:
    OpenGLRenderer();
    ~OpenGLRenderer() override;

    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;
    void synchronize(QQuickFramebufferObject *item) override;

private:
    void initialize();
    void uploadVertices();

    bool                     m_initialized  = false;
    bool                     m_dirty        = false;
    QOpenGLShaderProgram     m_program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer            m_vbo { QOpenGLBuffer::VertexBuffer };

    int m_uColor     = -1;
    int m_uRound     = -1;
    int m_uPointSize = -1;

    // synced from OpenGLItem each frame
    QVector<QPointF> m_points;
    QColor           m_lineColor;
    float            m_lineWidth  = 2.0f;
    float            m_pointSize  = 14.0f;   // ← was missing
    int              m_vertexCount = 0;
};

// ─────────────────────────────────────────────────────────────────────────────
//  QML item
// ─────────────────────────────────────────────────────────────────────────────
class OpenGLItem : public QQuickFramebufferObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QVariantList points    READ points    WRITE setPoints    NOTIFY pointsChanged)
    Q_PROPERTY(QRectF worldRect       READ worldRect WRITE setWorldRect NOTIFY worldRectChanged)
    Q_PROPERTY(QColor lineColor       READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(float  lineWidth       READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(float  pointSize       READ pointSize WRITE setPointSize NOTIFY pointSizeChanged)  // ← was missing

public:
    explicit OpenGLItem(QQuickItem *parent = nullptr);
    QQuickFramebufferObject::Renderer *createRenderer() const override;

    QVariantList points()    const { return m_points;    }
    QRectF       worldRect() const { return m_worldRect; }
    QColor       lineColor() const { return m_lineColor; }
    float        lineWidth() const { return m_lineWidth; }
    float        pointSize() const { return m_pointSize; }   // ← was missing

    void setPoints   (const QVariantList &v);
    void setWorldRect(const QRectF &v);
    void setLineColor(const QColor &v);
    void setLineWidth(float v);
    void setPointSize(float v);   // ← was missing

signals:
    void pointsChanged();
    void worldRectChanged();
    void lineColorChanged();
    void lineWidthChanged();
    void pointSizeChanged();   // ← was missing

private:
    friend class OpenGLRenderer;
    QVector<QPointF> ndcPoints() const;

    QVariantList m_points;
    QRectF       m_worldRect;
    QColor       m_lineColor { "#00d4ff" };
    float        m_lineWidth { 2.0f };
    float        m_pointSize { 14.0f };   // ← was missing
};