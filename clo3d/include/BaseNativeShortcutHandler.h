#ifndef FASHIONDESIGNAPPS_BASENATIVEEVENTHANDLER_H
#define FASHIONDESIGNAPPS_BASENATIVEEVENTHANDLER_H

#include <QKeySequence>

class BaseNativeShortcutHandler {
protected:
    explicit BaseNativeShortcutHandler(const QKeySequence& shortcut);
    virtual ~BaseNativeShortcutHandler();

    void setShortcut(const QKeySequence &shortcut);
public:
    virtual void handle() = 0;

    static BaseNativeShortcutHandler* getEventHandler(int id);
    static void registerShortcuts();
private:
    void registerShortcut() const;
protected:
    int id_;
    QKeySequence shortcut_;
};


#endif //FASHIONDESIGNAPPS_BASENATIVEEVENTHANDLER_H