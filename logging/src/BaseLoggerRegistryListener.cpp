#include "BaseLoggerRegistryListener.h"

#include "LoggerRegistry.h"

using namespace Logging;

BaseLoggerRegistryListener::BaseLoggerRegistryListener(LoggerRegistry& registry): registry_(registry) {
    registry.addListener(this);
}
