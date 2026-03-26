#include "SamplesExtension.h"

#include "DialogPreference.h"

#include <QMenu>

void SamplesExtension::configureMenu(QMenu* extensionMenu) {
    const auto samplesMenu = extensionMenu->addMenu("Samples");

    samplesMenu->addAction("User Settings", [] {
        const auto dialogPreference = new DialogPreference(ExtensionsManager::mainWindow);
        dialogPreference->exec();
    });
}
