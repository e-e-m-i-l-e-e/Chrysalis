#ifndef CHRYSALIS_BASELOGGERREGISTRYLISTENER_H
#define CHRYSALIS_BASELOGGERREGISTRYLISTENER_H

class Logger;
class LoggerRegistry;

class BaseLoggerRegistryListener {
protected:
    explicit BaseLoggerRegistryListener(LoggerRegistry& registry);
    virtual ~BaseLoggerRegistryListener() = default;
public:
    virtual void loggerAdded(Logger* logger) = 0;
protected:
    LoggerRegistry& registry_;
};

#endif //CHRYSALIS_BASELOGGERREGISTRYLISTENER_H