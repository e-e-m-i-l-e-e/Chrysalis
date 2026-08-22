#include "HookHandle.h"

HookHandle::HookHandle(std::list<std::function<void()>>& executeLater, std::function<void()> remover)
    : executeLater_(&executeLater), remover_(std::move(remover)) {}

void HookHandle::remove() const {
    executeLater_->push_back(remover_);
}
