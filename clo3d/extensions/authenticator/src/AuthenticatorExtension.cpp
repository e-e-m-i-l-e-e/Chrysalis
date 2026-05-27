#include "AuthenticatorExtension.h"

#define LOGGER_NAME "Authenticator Extension"

#include <QUrl>
#include <QThread>
#include <QPointer>
#include <QApplication>
#include <QDesktopServices>
#include <QtCore/private/qhooks_p.h>

#include "Logging.h"
#include "HooksManager.h"

// TODO:
//  - Class for qHookData, constructionQueue, loginDialog
//  - Intercept other HTTP(S) calls

QWidget* loginDialog;
QObject* authenticationProcessor;
QVector<QPointer<QObject>> constructionQueue;

bool isObjectOfClass(const QObject* object, const QString& className) {
    return className == object->metaObject()->className();
}

void AuthenticatorExtension::install() {
    qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(+[](QObject *object) {
        for (int i = 0; i < constructionQueue.size(); i++) {
            if (auto pointer = constructionQueue.at(i)) {
                if (QObject* obj = pointer.data()) {
                    if (!authenticationProcessor && isObjectOfClass(obj, "AuthenticationProcessor")) {
                        authenticationProcessor = obj;
                    } else if (!loginDialog && isObjectOfClass(obj, "CloUICommon::LoginDialog")) {
                        loginDialog = qobject_cast<QWidget*>(obj);
                    }
                }
                constructionQueue.removeAt(i);
                i--;
            }
        }
        constructionQueue.append(QPointer(object));
    });
    HooksManager::addBefore<&QApplication::exec>([](const HookHandle& handle) {
        loginDialog->dumpObjectInfo();
        authenticationProcessor->dumpObjectInfo();

        LOG_INFO("Skipping logging in");
        QMetaObject::invokeMethod(authenticationProcessor, "SucceedAuthentication");
        QMetaObject::invokeMethod(loginDialog, "SignInWithCloset");

        qtHookData[QHooks::AddQObject] = 0;
        handle.remove();
    });
    HooksManager::addIgnore<&QDesktopServices::openUrl>([](const HookHandle &handle, bool &ignore, bool &ret, const QUrl &url) {
        if (url.toString().startsWith("https://style.clo-set.com/en/account/signin?productId=40")) {
            LOG_INFO("Bypassing login URL: {}", url.toString().toStdString());
            ignore = true;
            ret = true;
        }
    });
}
