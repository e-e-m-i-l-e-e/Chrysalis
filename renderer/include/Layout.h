#ifndef CHRYSALIS_LAYOUT_H
#define CHRYSALIS_LAYOUT_H

#include <cstddef>

namespace Chrysalis {
    class Layout {
    public:
        explicit Layout(size_t offset, size_t count);

        const size_t& offset() const;
        const size_t& count() const;
    private:
        const size_t offset_;
        const size_t count_;
    };
}

#endif //CHRYSALIS_LAYOUT_H