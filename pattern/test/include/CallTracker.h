#ifndef CHRYSALIS_CALLTRACKER_H
#define CHRYSALIS_CALLTRACKER_H

#include <mutex>
#include <condition_variable>

namespace Chrysalis {
    class CallTracker {
    public:
        CallTracker& operator++();
        bool wait(size_t n, std::chrono::milliseconds timeout);
        int count();
    private:
        std::mutex mutex_;
        std::condition_variable cv_;
        size_t count_ = 0;
    };
}

#endif // CHRYSALIS_CALLTRACKER_H
