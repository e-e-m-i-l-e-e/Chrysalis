#ifndef CLOEXTENSIONS_EXTENSIONSMANAGER_H
#define CLOEXTENSIONS_EXTENSIONSMANAGER_H

#include <QLabel>

#include <vector>
#include <Windows.h>

#include "Extension.h"
#include "ExtensionsSettings.h"

class ExtensionsManager {

    friend Extension;
    friend BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved);

    static void setMessage(const QString& message);
    static void install();

    inline static QLabel* backgroundMessage_;
public:

    static void registerExtension(Extension* extension);

    static void setMessage(const QString& extensionName, const QString& message, bool logMessage = false);
    static void clearMessage();

    inline static std::vector<Extension*> extensions;
    inline static ExtensionsSettings* extensionsSettings;

    inline static QFrame* mainWindow;
};

#define UI_MESSAGE(message) ExtensionsManager::setMessage(LOGGER_NAME, message, false);
#define LOG_UI_MESSAGE(message) ExtensionsManager::setMessage(LOGGER_NAME, message, true);

#endif //CLOEXTENSIONS_EXTENSIONSMANAGER_H