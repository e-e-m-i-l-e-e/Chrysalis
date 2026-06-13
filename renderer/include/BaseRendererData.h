#ifndef CHRYSALIS_BASERENDERERDATA_H
#define CHRYSALIS_BASERENDERERDATA_H

#include <Vertex2f.h>

template<typename V>
requires std::is_base_of_v<Vertex2f, V>
class BaseRendererData {
protected:
    explicit BaseRendererData() = default;
public:
    virtual ~BaseRendererData() = default;

    [[nodiscard]] static size_t stride() {
        return sizeof(V);
    }
    [[nodiscard]] static std::vector<std::pair<int, void*>> layout() {
        return V::getLayout();
    }

    virtual V* vbo() = 0;
    virtual size_t count() = 0;

    size_t size() {
        return count() * sizeof(V);
    }
    void updateVBO() {
        shouldUpload_ = true;
    }
    [[nodiscard]] bool shouldUpload() {
        return shouldUpload_;
    }
private:
    bool shouldUpload_ = true;
};

#endif //CHRYSALIS_BASERENDERERDATA_H