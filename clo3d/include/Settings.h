#ifndef FASHIONDESIGNAPPS_SETTINGS_H
#define FASHIONDESIGNAPPS_SETTINGS_H

#include <QSettings>

class Settings {
public:
    explicit Settings(const QString& groupName, QSettings* settings);
    ~Settings();
    void* operator new(std::size_t size) = delete;

    void setValue(const QString &key, const QVariant &value) const;
    [[nodiscard]] QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;
private:
    QSettings* settings_;
};

#endif //FASHIONDESIGNAPPS_SETTINGS_H