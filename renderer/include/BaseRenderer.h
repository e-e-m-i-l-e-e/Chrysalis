#ifndef CHRYSALIS_BASERENDERER_H
#define CHRYSALIS_BASERENDERER_H

#include <vector>

#include <glad/gl.h>

#include "Vertex2f.h"

template<typename V>
requires std::is_base_of_v<Vertex2f, V>
class BaseRenderer {
protected:
    virtual ~BaseRenderer() {
        if (vbo_ != 0) glDeleteBuffers(1, &vbo_);
        if (vao_ != 0) glDeleteVertexArrays(1, &vao_);
    }

public:
    void upload() {
        if (!shouldUpload_) return;

        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(
            GL_ARRAY_BUFFER,
            data_.size() * sizeof(V),
            data_.data(),
            GL_DYNAMIC_DRAW
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        shouldUpload_ = false;
    }

    void shouldUpload() {
        shouldUpload_ = true;
    }

    virtual void initialize() {
        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        glGenBuffers(1, &vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);

        glBufferData(GL_ARRAY_BUFFER, data_.size() * sizeof(V), data_.data(), GL_DYNAMIC_DRAW);

        const auto layout = V::getLayout();

        for (GLuint i = 0; i < layout.size(); i++) {
            const auto& [count, offset] = layout[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, count, GL_FLOAT, GL_FALSE, sizeof(V), offset);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        shouldUpload_ = false;
    }

    void render() {
        glBindVertexArray(vao_);
        draw();
        glBindVertexArray(0);
    }

    virtual void draw() = 0;

protected:
    std::vector<V> data_;

private:
    GLuint vbo_ = 0;
    GLuint vao_ = 0;
    bool shouldUpload_ = true;
};

#endif //CHRYSALIS_BASERENDERER_H