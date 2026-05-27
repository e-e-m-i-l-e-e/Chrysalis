#include "BaseLoggerRegistryListener.h"

#include "LoggerRegistry.h"

BaseLoggerRegistryListener::BaseLoggerRegistryListener(LoggerRegistry& registry): registry_(registry) {
    registry.addListener(this);
}
