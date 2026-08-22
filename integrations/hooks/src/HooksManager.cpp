#include "HooksManager.h"

void HooksManager::remove(void* address) {
    const auto it = _hooks.find(address);
    if (it == _hooks.end()) return;
    const auto *hook = it->second;
    _hooks.erase(it);
    delete hook; // ~Hook() → unHook() then ~HookBase()
}

std::string HooksManager::getName(void* address)  {
    const auto it = _hooks.find(address);
    if (it == _hooks.end()) return "<unknown>";

    std::string raw = typeid(*it->second).name();

    // The template instantiation string contains the original function
    // signature — extract the last "Namespace::Method(" token from it.
    static const std::regex re(R"(<[^>]*?(\w+::\w+)\()");
    std::smatch match;
    if (std::regex_search(raw, match, re) && match.size() > 1)
        return match[1].str();
    return raw;
}
