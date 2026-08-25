#ifndef CHRYSALIS_EVENTTRACKER_H
#define CHRYSALIS_EVENTTRACKER_H

#include <mutex>
#include <string>
#include <vector>

namespace Chrysalis {
    class EventTracker {
    public:
        void track(const std::string& event);
        std::vector<std::string> events();
    private:
        std::mutex mutex_;
        std::vector<std::string> events_;
    };
}

#endif // CHRYSALIS_EVENTTRACKER_H
