#pragma once

#include <QQuickFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QVariantList>
#include <QColor>
#include <QRectF>

#include "DistancedVertex.h"

class OpenGLItemOLD;

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
class OpenGLRendererOLD : public QQuickFramebufferObject::Renderer,
                       protected QOpenGLFunctions
{
public:
    OpenGLRendererOLD();
    ~OpenGLRendererOLD() override;

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
    QOpenGLBuffer            m_ebo { QOpenGLBuffer::IndexBuffer };

    int m_uColor     = -1;
    int m_uRound     = -1;
    int m_uPointSize = -1;
    int m_uDashed     = -1;
    int m_uDashSize     = -1;
    int m_uGapSize = -1;

    // Three data sets, kept in NDC space
    QVector<QPointF> m_shapeVerts;   // triangles  (N must be divisible by 3)
    QList<DistancedVertex> m_dotVerts;     // individual dots
    std::vector<int> m_indices;     // individual dots

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
class OpenGLItemOLD : public QQuickFramebufferObject
{
    Q_OBJECT
    QML_ELEMENT

    // --- data ---
    Q_PROPERTY(QVariantList shapePoints READ shapePoints WRITE setShapePoints NOTIFY shapePointsChanged)
    // Q_PROPERTY(QVariantList dotPoints   READ dotPoints   WRITE setDotPoints   NOTIFY dotPointsChanged)
    Q_PROPERTY(QRectF worldRect         READ worldRect   WRITE setWorldRect   NOTIFY worldRectChanged)

    // --- appearance ---
    Q_PROPERTY(QColor fillColor  READ fillColor  WRITE setFillColor  NOTIFY fillColorChanged)
    Q_PROPERTY(QColor edgeColor  READ edgeColor  WRITE setEdgeColor  NOTIFY edgeColorChanged)
    Q_PROPERTY(QColor dotColor   READ dotColor   WRITE setDotColor   NOTIFY dotColorChanged)
    Q_PROPERTY(float  lineWidth  READ lineWidth  WRITE setLineWidth  NOTIFY lineWidthChanged)
    Q_PROPERTY(float  pointSize  READ pointSize  WRITE setPointSize  NOTIFY pointSizeChanged)

public:
    explicit OpenGLItemOLD(QQuickItem *parent = nullptr);
    QQuickFramebufferObject::Renderer *createRenderer() const override;

    QVariantList shapePoints() const { return m_shapePoints; }
    QList<DistancedVertex> dotPoints()   const { return m_dotPoints;   }
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
    friend class OpenGLRendererOLD;

    // Converts any QVariantList<QPointF> → NDC, using the shared world rect
    QVector<QPointF> toNdc(const QVariantList &src, const QRectF &rect) const;
    QList<DistancedVertex> toNdc2(const QList<DistancedVertex> &src, const QRectF &rect) const;
    QRectF           autoWorldRect() const;  // union of all points

    QVariantList m_shapePoints;
    QVector<QVector<QPointF>> m_edgeLoops;
    QList<DistancedVertex> m_dotPoints;
    QRectF       m_worldRect;
    std::vector<int> m_indices;

    QColor m_fillColor { 26,  102, 128, 120 };   // ~50 % cyan
    QColor m_edgeColor { "#00d4ff" };
    QColor m_dotColor  { "#ffffff" };
    float  m_lineWidth { 2.0f };
    float  m_pointSize { 14.0f };
};