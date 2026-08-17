#ifndef CHRYSALIS_EXTENSIONSMANAGER_H
#define CHRYSALIS_EXTENSIONSMANAGER_H

#include <QDir>
#include <QLabel>
#include <QToolButton>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "BaseExtension.h"
#include "CommandRunner.h"
#include "ExtensionsSettings.h"
#include "CLO3DExtensionExport.h"

class CLO3D_EXTENSION ExtensionsManager {
    friend BaseExtension;
#ifdef _WIN32
    friend BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved);
#endif

    static void setMessage(const QString& message);
    static void install();

    inline static QLabel* backgroundMessage_;
public:

    static void addExtension(std::unique_ptr<BaseExtension> extension);

    static void setMessage(const char* extensionName, const QString& message, bool logMessage = false);
    static void clearMessage();

    inline static std::forward_list<std::unique_ptr<BaseExtension>> extensions;
    inline static ExtensionsSettings* extensionsSettings;

    inline static QFrame* mainWindow;

    inline static QToolButton* action;
    inline static CommandRunner* commandRunner_;

    static inline auto ROOT_EXTENSIONS_DIR = QDir(QString(CLO_HOME) + "/.extensions");
};

#define UI_MESSAGE(message) ExtensionsManager::setMessage(LOGGER_NAME, message, false);
#define LOG_UI_MESSAGE(message) ExtensionsManager::setMessage(LOGGER_NAME, message, true);

#endif //CHRYSALIS_EXTENSIONSMANAGER_H