#ifndef FASHIONDESIGNAPPS_BASERENDERER_H
#define FASHIONDESIGNAPPS_BASERENDERER_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

#include "Vertex.h"

template<typename V> requires std::is_base_of_v<Vertex, V>
class BaseRenderer: public QOpenGLFunctions {
protected:
    virtual ~BaseRenderer() = default;
public:
    virtual void initialize() {
        initializeOpenGLFunctions();

        vbo.create();
        vbo.bind();
        vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);

        vao.create();
        vao.bind();
        const auto layout = V::getLayout();
        for (int i = 0; i < layout.size(); i++) {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, layout[i].size, GL_FLOAT, GL_FALSE, sizeof(V), layout[i].offset);
        }
        vao.release();
        vbo.release();
    }
    virtual void render() = 0;
protected:
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
};

#endif //FASHIONDESIGNAPPS_BASERENDERER_H