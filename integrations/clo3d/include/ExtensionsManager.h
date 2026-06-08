#ifndef CHRYSALIS_EXTENSIONSMANAGER_H
#define CHRYSALIS_EXTENSIONSMANAGER_H

#include <QDir>
#include <QLabel>

#include <Windows.h>

#include "BaseExtension.h"
#include "CommandRunner.h"
#include "ExtensionsSettings.h"

class ExtensionsManager {
    friend BaseExtension;
    friend BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved);

    static void setMessage(const QString& message);
    static void install();

    inline static QLabel* backgroundMessage_;
public:

    static void addExtension(BaseExtension* extension);

    static void setMessage(const char* extensionName, const QString& message, bool logMessage = false);
    static void clearMessage();

    inline static std::forward_list<BaseExtension*> extensions;
    inline static ExtensionsSettings* extensionsSettings;

    inline static QFrame* mainWindow;

    inline static QToolButton* action;
    inline static CommandRunner* commandRunner_;

    static inline auto ROOT_EXTENSIONS_DIR = QDir(QString(CLO_HOME) + "/.extensions");
};

#define UI_MESSAGE(message) ExtensionsManager::setMessage(LOGGER_NAME, message, false);
#define LOG_UI_MESSAGE(message) ExtensionsManager::setMessage(LOGGER_NAME, message, true);

#endif //CHRYSALIS_EXTENSIONSMANAGER_H