#ifndef CHRYSALIS_BASERENDERERDATA_H
#define CHRYSALIS_BASERENDERERDATA_H

#include <Vertex2f.h>

namespace Chrysalis {
    template<typename V>
    requires std::is_base_of_v<Vertex2f, V>
    class BaseRendererData {
    protected:
        explicit BaseRendererData() = default;
    public:
        virtual ~BaseRendererData() = default;

        virtual size_t size() = 0;
        virtual std::vector<V> vbo() = 0;

        virtual void updateVBO() {
            shouldUpload_ = true;
        }
        [[nodiscard]] bool shouldUpload() {
            if (shouldUpload_) {
                shouldUpload_ = false;
                return true;
            }
            return shouldUpload_;
        }
    private:
        bool shouldUpload_ = true;
    };
}

#endif //CHRYSALIS_BASERENDERERDATA_H