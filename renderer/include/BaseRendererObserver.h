#ifndef CHRYSALIS_BASEPROJECTRENDEREROBSERVER_H
#define CHRYSALIS_BASEPROJECTRENDEREROBSERVER_H

namespace Chrysalis {
    class BaseRendererObserver {
    public:
        virtual ~BaseRendererObserver() = default;
        virtual void vboChanged() = 0;
    protected:
        explicit BaseRendererObserver() = default;
    };
}

#endif // CHRYSALIS_BASEPROJECTRENDEREROBSERVER_H
