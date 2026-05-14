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
//  Helper: a slice of the shared VBO
// ─────────────────────────────────────────────────────────────────────────────
struct DrawBatch {
    int first = 0;   // vertex index inside VBO
    int count = 0;
};

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

    bool                     m_initialized = false;
    bool                     m_dirty       = false;

    QOpenGLShaderProgram     m_program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer            m_vbo { QOpenGLBuffer::VertexBuffer };

    int m_uColor     = -1;
    int m_uRound     = -1;
    int m_uPointSize = -1;

    // Three data sets, kept in NDC space
    QVector<QPointF> m_shapeVerts;   // triangles  (N must be divisible by 3)
    QVector<QPointF> m_dotVerts;     // individual dots

    DrawBatch m_shapeBatch;
    QVector<QVector<QPointF>> m_edgeLoops;   // one inner vector per loop
    QVector<DrawBatch>        m_edgeBatches;
    DrawBatch m_dotBatch;

    // Appearance (synced each frame)
    QColor m_fillColor  { "#1a6680" };   // semi-transparent fill
    QColor m_edgeColor  { "#00d4ff" };
    QColor m_dotColor   { "#ffffff" };
    float  m_lineWidth  = 2.0f;
    float  m_pointSize  = 14.0f;
};

// ─────────────────────────────────────────────────────────────────────────────
//  QML item
// ─────────────────────────────────────────────────────────────────────────────
class OpenGLItem : public QQuickFramebufferObject
{
    Q_OBJECT
    QML_ELEMENT

    // --- data ---
    Q_PROPERTY(QVariantList shapePoints READ shapePoints WRITE setShapePoints NOTIFY shapePointsChanged)
    Q_PROPERTY(QVariantList dotPoints   READ dotPoints   WRITE setDotPoints   NOTIFY dotPointsChanged)
    Q_PROPERTY(QRectF worldRect         READ worldRect   WRITE setWorldRect   NOTIFY worldRectChanged)

    // --- appearance ---
    Q_PROPERTY(QColor fillColor  READ fillColor  WRITE setFillColor  NOTIFY fillColorChanged)
    Q_PROPERTY(QColor edgeColor  READ edgeColor  WRITE setEdgeColor  NOTIFY edgeColorChanged)
    Q_PROPERTY(QColor dotColor   READ dotColor   WRITE setDotColor   NOTIFY dotColorChanged)
    Q_PROPERTY(float  lineWidth  READ lineWidth  WRITE setLineWidth  NOTIFY lineWidthChanged)
    Q_PROPERTY(float  pointSize  READ pointSize  WRITE setPointSize  NOTIFY pointSizeChanged)

public:
    explicit OpenGLItem(QQuickItem *parent = nullptr);
    QQuickFramebufferObject::Renderer *createRenderer() const override;

    QVariantList shapePoints() const { return m_shapePoints; }
    QVariantList dotPoints()   const { return m_dotPoints;   }
    QRectF       worldRect()   const { return m_worldRect;   }
    QColor       fillColor()   const { return m_fillColor;   }
    QColor       edgeColor()   const { return m_edgeColor;   }
    QColor       dotColor()    const { return m_dotColor;    }
    float        lineWidth()   const { return m_lineWidth;   }
    float        pointSize()   const { return m_pointSize;   }

    void setShapePoints(const QVariantList &v);
    void setEdgePoints (const QVariantList &v);
    void setDotPoints  (const QVariantList &v);
    void setWorldRect  (const QRectF &v);
    void setFillColor  (const QColor &v);
    void setEdgeColor  (const QColor &v);
    void setDotColor   (const QColor &v);
    void setLineWidth  (float v);
    void setPointSize  (float v);

signals:
    void shapePointsChanged();
    void edgePointsChanged();
    void dotPointsChanged();
    void worldRectChanged();
    void fillColorChanged();
    void edgeColorChanged();
    void dotColorChanged();
    void lineWidthChanged();
    void pointSizeChanged();

private:
    friend class OpenGLRenderer;

    // Converts any QVariantList<QPointF> → NDC, using the shared world rect
    QVector<QPointF> toNdc(const QVariantList &src, const QRectF &rect) const;
    QRectF           autoWorldRect() const;  // union of all points

    QVariantList m_shapePoints;
    QVector<QVector<QPointF>> m_edgeLoops;
    QVariantList m_dotPoints;
    QRectF       m_worldRect;

    QColor m_fillColor { 26,  102, 128, 120 };   // ~50 % cyan
    QColor m_edgeColor { "#00d4ff" };
    QColor m_dotColor  { "#ffffff" };
    float  m_lineWidth { 2.0f };
    float  m_pointSize { 14.0f };
};