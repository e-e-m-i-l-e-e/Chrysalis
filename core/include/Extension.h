#ifndef CLOEXTENSIONS_EXTENSION_H
#define CLOEXTENSIONS_EXTENSION_H

#include <QMenu>

class Extension {
protected:
    explicit Extension() = default;
    virtual ~Extension() = default;
public:
    virtual void configureMenu(QMenu* extensionMenu) {}
    virtual void configureStatusBar(QWidget* parent) {}
};

#endif //CLOEXTENSIONS_EXTENSION_H