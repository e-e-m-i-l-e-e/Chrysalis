#include "EventTracker.h"

using namespace Chrysalis;

void EventTracker::track(const std::string& event) {
    std::lock_guard lock(mutex_);
    events_.push_back(event);
}

std::vector<std::string> EventTracker::events() {
    std::lock_guard lock(mutex_);
    return events_;
}
