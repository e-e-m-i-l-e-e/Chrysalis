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
    void upload() {
        if (shouldUpload_) {
            vbo.bind();
            vbo.allocate(data_.data(), data_.size() * sizeof(V));
            vbo.release();
            shouldUpload_ = false;
        }
    }
    void shouldUpload() {
        shouldUpload_ = true;
    }
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
        upload();
    }
    virtual void render() = 0;
protected:
    std::vector<V> data_;

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
private:
    bool shouldUpload_ = true;
};

#endif //FASHIONDESIGNAPPS_BASERENDERER_H