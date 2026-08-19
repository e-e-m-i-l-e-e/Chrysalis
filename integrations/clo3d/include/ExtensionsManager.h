#ifndef CHRYSALIS_EXTENSIONSMANAGER_H
#define CHRYSALIS_EXTENSIONSMANAGER_H

#include <QDir>
#include <QLabel>
#include <QTimer>
#include <QToolButton>

#ifdef _WIN32
#include <Windows.h>
BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved);
#endif

#include "TaskExecutor.h"
#include "BaseExtension.h"
#include "CommandRunner.h"
#include "ExtensionsSettings.h"
#include "CLO3DExtensionExport.h"

namespace CLO3D {
    constexpr auto ROOT_EXTENSIONS_DIR = CLO_HOME "/.extensions";

    class CLO3D_EXTENSION ExtensionsManager {
        friend BaseExtension;
#ifdef _WIN32
        friend BOOL WINAPI ::DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved);
#endif

        static void setMessage(const QString& message);
        static void install();

        inline static QLabel* backgroundMessage_;
        inline static QTimer* backgroundMessageTimer_;
    public:

        static void addExtension(std::unique_ptr<BaseExtension> extension);

        static void setMessage(const char* extensionName, const QString& message, bool logMessage = false);
        static void clearMessage();

        inline static std::forward_list<std::unique_ptr<BaseExtension>> extensions;
        inline static ExtensionsSettings* extensionsSettings;

        inline static QFrame* mainWindow;

        inline static QToolButton* action;
        inline static CommandRunner* commandRunner_;
        inline static TaskExecutor executor;
    };
}

#define UI_MESSAGE(message) ExtensionsManager::setMessage(LOGGER_NAME, message, false);
#define LOG_UI_MESSAGE(message) ExtensionsManager::setMessage(LOGGER_NAME, message, true);

#endif //CHRYSALIS_EXTENSIONSMANAGER_H