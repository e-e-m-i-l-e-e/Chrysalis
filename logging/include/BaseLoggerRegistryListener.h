#ifndef FASHIONDESIGNAPPS_BASELOGGERREGISTRYLISTENER_H
#define FASHIONDESIGNAPPS_BASELOGGERREGISTRYLISTENER_H

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

#endif //FASHIONDESIGNAPPS_BASELOGGERREGISTRYLISTENER_H