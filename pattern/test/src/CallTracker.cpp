#include "CallTracker.h"

using namespace Chrysalis;

CallTracker& CallTracker::operator++()  {
    std::lock_guard lock(mutex_);
    ++count_;
    cv_.notify_all();
    return *this;
}

bool CallTracker::wait(const size_t n, const std::chrono::milliseconds timeout) {
    std::unique_lock lock(mutex_);
    return cv_.wait_for(lock, timeout, [&] {
        return count_ >= n;
    });
}

int CallTracker::count() {
    std::lock_guard lock(mutex_);
    return count_;
}