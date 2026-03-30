#include "ExtensionsManager.h"

#define LOGGER_NAME "Extensions Manager"

#include <QApplication>
#include <QMenuBar>

#include "ExtensionsSettings.h"

#include "HooksManager.h"
#include "MVStatusBar.h"

void ExtensionsManager::registerExtension(Extension *extension) {
    extensions.push_back(extension);
}

void ExtensionsManager::install() {
    HooksManager::addBefore<&QObject::connect>([&](const HookHandle& handle, const QObject *sender, const char *signal,
                        const QObject *receiver, const char *member, Qt::ConnectionType connection) {

    });
    HooksManager::addBefore<&QApplication::exec>([&](const HookHandle &handle) {

        QMenuBar* menu = nullptr;

        for (const auto widget: QApplication::allWidgets()) {
            // Configure main window
            if (widget->objectName() == "TitleFrame") {
                mainWindow = dynamic_cast<QFrame*>(widget);
                LOG_INFO("Main window has been detected by Extensions Manager.");
            }

            // Getting menu bar for further configuration
            else if (widget->objectName() == "myMenuBar") menu = qobject_cast<QMenuBar*>(widget);

            // Inject QLabel for displaying messages from background processes into bottom status bar.
            else if (QString(widget->metaObject()->className()) == "MVStatusBar") {
                for (const auto statusBar = dynamic_cast<MVStatusBar*>(widget);
                     const auto child: statusBar->children()) {
                    if (child->metaObject() == &QWidget::staticMetaObject && !child->children().empty()) {
                        const auto parent = qobject_cast<QWidget*>(child);
                        backgroundMessage_ = new QLabel(parent);
                        backgroundMessage_->setGeometry(statusBar->width() / 2, 2, 500, 20);
                        UTILITY_API->UpdateCloStyleForPlugIn(backgroundMessage_);
                        backgroundMessage_->show();

                        for (const auto extension: extensions) {
                            extension->configureStatusBar(parent);
                        }
                    }
                }
            }

            for (const auto extension: extensions) {
                extension->configure(widget);
            }
        }

        if (!menu) {
            LOG_CRITICAL("Menu was not found");
            exit(1);
        }

        // Configuring menu
        const auto extensionsMenu = menu->addMenu("Extensions");

        extensionsSettings = new ExtensionsSettings(mainWindow);
        const QAction *extensionsSettingsMenu = extensionsMenu->addAction("Extensions Settings");
        QObject::connect(extensionsSettingsMenu, &QAction::triggered, extensionsSettings, &ExtensionsSettings::exec);

        for (const auto extension: extensions) {
            extension->configureMenu(extensionsMenu);
        }

        LOG_INFO("Extensions menu has been added to myMenuBar");
        handle.remove();
    });
}

void ExtensionsManager::setMessage(const QString &message) {
    QMetaObject::invokeMethod(backgroundMessage_, [message] {
        backgroundMessage_->setText(message);
        backgroundMessage_->repaint();
    });
}

void ExtensionsManager::setMessage(const QString &extensionName, const QString &message,
                                   const bool logMessage) {
    if (logMessage) LOG_INFO_TO(extensionName.toStdString(), "{}", message.toStdString());
    setMessage(QString("<img src=':/Resources/CommonIcon/Title Bullet Secondary.svg' width='11' height='11'><b>%1:</b> %2").arg(extensionName).arg(message));
}

void ExtensionsManager::clearMessage() {
    setMessage("");
}
