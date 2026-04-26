#include "ExtensionsManager.h"

#define LOGGER_NAME "Extensions Manager"

#include <QApplication>
#include <QCheckBox>
#include <QMenuBar>
#include <QMenu>
#include <QDoubleSpinBox>

#include <QDesktopServices>
#include <QLayout>
#include <qthreadpool.h>

// #include <QtCore/private/qobject_p.h>
// #include <QtCore/private/qfiledevice_p.h>
// #include <QtCore/qobjectdefs.h>

#include <CLOAPIInterface.h>
#include <QDockWidget>

#include "ExtensionsSettingsDialog.h"
#include "GeneralUIExporterOptions.h"

#include "HooksManager.h"
#include "JsonUIExporterOptions.h"
#include "UIExporterToolSettingsWidget.h"
#include "XmlUIExporterOptions.h"

void ExtensionsManager::registerExtension(Extension *extension) {
    extensions.push_back(extension);
}
#include <QToolButton>
#include <QOpenGLWidget>

void ExtensionsManager::install() {
    // Forward all CLO3D logging into Extension's logger
    HooksManager::addIgnore<&qInstallMessageHandler>([](const HookHandle&, bool& ignore, QtMessageHandler&, QtMessageHandler&) {
        ignore = true;
    });
    HooksManager::addAfter<&QWidget::show>([](const HookHandle& handle, QWidget* this_) {
        if (this_->objectName() == " TitleFrame") {
            LOG_INFO("Main window has been detected by Extensions Manager. Setting up UI.");
            mainWindow = dynamic_cast<QFrame*>(this_);
            for (const auto widget: QApplication::allWidgets()) {
                for (const auto extension: extensions) {
                    extension->configure(widget);
                }
            }
        } else if (this_->objectName() == "myMenuBar") {
            LOG_INFO("Configuring \"Extensions\" menu.");
            const auto menuBar = qobject_cast<QMenuBar *>(this_);
            const auto extensionsMenu = menuBar->addMenu("Extensions");

            extensionsSettings = new UI::ExtensionsSettingsDialog(mainWindow);
            // extensionsSettings = new ExtensionsSettings(mainWindow);
            const QAction *extensionsSettingsMenu = extensionsMenu->addAction("Extensions Settings");
            // QObject::connect(extensionsSettingsMenu, &QAction::triggered, extensionsSettings, &ExtensionsSettings::exec);
            QObject::connect(extensionsSettingsMenu, &QAction::triggered, []() {

                const auto settings = new QSettings("eemilee.me", "CLO3D Extensions");
                auto uiExporterSettings = new UIExporterToolSettings();

                auto generalUIExporterOptions = std::make_shared<GeneralUIExporterOptions>(settings);
                auto jsonUIExporterOptions = std::make_shared<JsonUIExporterOptions>(settings);
                auto xmlUIExporterOptions = std::make_shared<XmlUIExporterOptions>(settings);

                uiExporterSettings->addOptions(xmlUIExporterOptions);
                uiExporterSettings->addOptions(jsonUIExporterOptions);
                uiExporterSettings->addOptions(generalUIExporterOptions);

                auto uiExporterSettingsWidget = new UI::UIExporterToolSettingsWidget(*uiExporterSettings);
                extensionsSettings->addPage(uiExporterSettingsWidget);
                extensionsSettings->exec();
            });

            for (const auto extension: extensions) {
                extension->configureMenu(extensionsMenu);
            }
        } else if (QString(this_->metaObject()->className()) == "MVStatusBar") {
            LOG_INFO("Configuring status bar.");
            for (const auto statusBar = dynamic_cast<QDockWidget*>(this_);
                 const auto child: statusBar->children()) {
                if (child->metaObject() == &QWidget::staticMetaObject && !child->children().empty()) {
                    const auto parent = qobject_cast<QWidget *>(child);
                    backgroundMessage_ = new QLabel(parent);
                    backgroundMessage_->setGeometry(statusBar->width() / 2, 2, 500, 20);
                    UTILITY_API->UpdateCloStyleForPlugIn(backgroundMessage_);
                    backgroundMessage_->show();

                    for (const auto extension: extensions) {
                        extension->configureStatusBar(parent);
                    }
                }
            }
        } else if (const auto openGL = qobject_cast<QOpenGLWidget*>(this_)) {
            LOG_DEBUG("OpenGL widget: {}", openGL->objectName().toStdString());
        }
    });

    HooksManager::addAfter<&QObject::setObjectName>([](const HookHandle&, QObject* this_, const QString& name) {
        if (name.contains("MeasureID")) {
            LOG_INFO("Measure: {}. Class: {}", name.toStdString(), this_->metaObject()->className());
            if (const auto spinBox = qobject_cast<QDoubleSpinBox*>(this_)) {
                const auto parent = qobject_cast<QWidget*>(spinBox->parent());
                parent->layout()->addWidget(new QCheckBox(parent));
                spinBox->connect(spinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), [spinBox](double value) {
                    LOG_INFO("new value: {}", value);
                    // qDebug() << "Layout: " << spinBox->layout()->count();
                });
            }
        }
    });

    // HooksManager::addBefore<&fwrite>([](const HookHandle&, void const* _Buffer, size_t _ElementSize, size_t _ElementCount, FILE *) {
    //     size_t total = _ElementSize * _ElementCount;
    //
    //     if (!_Buffer || total == 0)
    //         return;
    //
    //     const char *data = static_cast<const char *>(_Buffer);
    //
    //     QByteArray arr(data, static_cast<int>(total));
    //
    //     // Try as text
    //     qDebug() << "fwrite text:" << arr;
    //
    //     // Always safe: hex dump
    //     qDebug() << "fwrite hex:" << arr.toHex();
    // });

    // using Fn = std::basic_ostream<char>& (std::basic_ostream<char>::*)(char);
    // Fn fn = [](std::basic_ostream<char>& os, char c) -> std::basic_ostream<char>& {
    //     return os.operator<<(c);
    //

    //.text:00007FFB1D6BB4B0 msvcp140.dll:$B4B0 #A8B0 <public: class std::basic_streambuf<wchar_t, struct std::char_traits<wchar_t>> * __cdecl std::basic_ios<wchar_t, struct std::char_traits<wchar_t>>::rdbuf(void) const>

    // .text:00007FFB1D6BB4B0 msvcp140.dll:$B4B0 #A8B0 <public: class std::basic_streambuf<wchar_t, struct std::char_traits<wchar_t>> * __cdecl std::basic_ios<wchar_t, struct std::char_traits<wchar_t>>::rdbuf(void) const>
    // HooksManager::addBefore<static_cast<std::basic_ostream<char, struct std::char_traits<char>>& (std::basic_ostream<char, struct std::char_traits<char>>::*)(float)>(&std::basic_ostream<char, struct std::char_traits<char>>::operator<<)>(
    //     [](const HookHandle &, std::basic_ostream<char, struct std::char_traits<char>>*, float _Val) {
    //     qDebug() << _Val;
    // });

    // HooksManager::addBefore<&std::basic_ostream<char>::put>(
    //     [](const HookHandle &, std::basic_ostream<char>* this_, char c) {
    //         qDebug() << "Char" << static_cast<int>(c);
    // });

   //  HooksManager::addBefore<&std::basic_streambuf<unsigned short>::getloc>(
   //     [](const HookHandle &, const std::basic_streambuf<unsigned short>*) {
   //         qDebug() << "Get LOCALE";
   // });

    // public: __cdecl std::basic_ostream<char, struct std::char_traits<char>>::basic_ostream<char, struct std::char_traits<char>>(class std::basic_streambuf<char, struct std::char_traits<char>> *, bool)
    // public: class std::locale __cdecl std::basic_streambuf<unsigned short, struct std::char_traits<unsigned short>>::getloc(void) const
    // public: __int64 __cdecl std::basic_streambuf<char, struct std::char_traits<char>>::sputn(char const *, __int64)
    // HooksManager::addBefore<&std::basic_streambuf<char>::sputn>(
    //     [](const HookHandle &, std::basic_streambuf<char>*, char const * text, std::streamsize size) {
    //         // if (text) qDebug() << "TEXT" << ret;
    // });

    //public: char __cdecl std::basic_ios<char, struct std::char_traits<char>>::widen(char) const

    // HooksManager::addBefore<&std::basic_ios<char>::widen>(
    //     [](const HookHandle &, const std::basic_ios<char>*, char c) {
    //         qDebug() << "WIDEN " << c;
    // });

    // HooksManager::addBefore<&QString::~QString>(
    //     [](const HookHandle &, QString* this_) {
    //         qDebug() << "WIDEN " << c;
    // });

    // HooksManager::addBefore<&std::basic_ostream<char, struct std::char_traits<char>>::init>(
    //     [](const HookHandle &, std::basic_streambuf<char>*, char const * text, std::streamsize size) {
    //         // qDebug() << "TEXT" << text;
    // });

    // public: class std::basic_ostream<unsigned short, struct std::char_traits<unsigned short>> & __cdecl std::basic_ostream<unsigned short, struct std::char_traits<unsigned short>>::operator<<(class std::basic_ostream<unsigned short, struct std::char_traits<un

    // HooksManager::addBefore<&std::basic_ostream<wchar_t>::flush>(
    //     [](const HookHandle &, std::basic_ostream<wchar_t>* this_) {
    //         const auto buf = this_->rdbuf();
    //         if (buf) {
    //             std::wstring data;
    //             for (auto ch = buf->sgetc(); ch != WEOF; ch = buf->snextc()) {
    //                 data += static_cast<wchar_t>(ch);
    //             }
    //             std::wcout << data;
    //         }
    // });

    //public: class std::basic_ostream<wchar_t, struct std::char_traits<wchar_t>> & __cdecl std::basic_ostream<wchar_t, struct std::char_traits<wchar_t>>::flush(void)
    //public: class std::basic_ostream<char, struct std::char_traits<char>> & __cdecl std::basic_ostream<char, struct std::char_traits<char>>::put(char)
    // public: class std::basic_ostream<char, struct std::char_traits<char>> & __cdecl std::basic_ostream<char, struct std::char_traits<char>>::operator<<(class std::basic_ostream<char, struct std::char_traits<char>> & (__cdecl *)(class std::basic_ostream<char,
    // public: class std::basic_streambuf<wchar_t, struct std::char_traits<wchar_t>> * __cdecl std::basic_ios<wchar_t, struct std::char_traits<wchar_t>>::rdbuf(void) const
    // (rdbuf<wchar_t> hook installed above via raw PLH::x64Detour — see s_rdbufWDetour)

    // HooksManager::addBefore<&vfprintf>([](const HookHandle &,
    //     FILE*       const _Stream,
    //     char const* const _Format,
    //     va_list           _ArgList) {
    //     qDebug() << "vprintf:" << _Format;
    // });

    // HooksManager::addBefore<&vfprintf>([](const HookHandle&, FILE* const _Stream, char const* const _Format, ...) {
    //     qDebug() << "fprintf format:" << _Format;
    // });

    // HooksManager::addBefore<&QObjectPrivate::addConnection>([&](const HookHandle& handle, const QObjectPrivate* obj, const int signal, const QObjectPrivate::Connection *c) {
    //     if (c->sender &&
    //         (!QString(c->sender->metaObject()->className()).startsWith("Q")
    //         || QString(c->sender->metaObject()->className()) == "QAction"
    //         || QString(c->sender->metaObject()->className()) == "QMenu")
    //         ) {
    //         const QMetaObject *mo = c->sender->metaObject();
    //         // Resolve signal name: signalIdx is 0-based counting only Signal methods
    //         // across the full metaobject hierarchy (including inherited).
    //         int sigCount = 0;
    //         for (int i = 0; i < mo->methodCount(); ++i) {
    //             if (mo->method(i).methodType() == QMetaMethod::Signal) {
    //                 if (sigCount == signal) {
    //                     LOG_DEBUG("addConnection  {}({})::{}  →  {}({})",
    //                               mo->className(),
    //                               c->sender->objectName().toStdString(),
    //                               mo->method(i).methodSignature().constData(),
    //                               c->receiver ? c->receiver.loadAcquire()->metaObject()->className() : "<null>",
    //                               c->receiver ? c->receiver.loadAcquire()->objectName().toStdString() : "");
    //
    //                     for (const QMetaObject *m = mo; m != nullptr; m = m->superClass()) {
    //                         if (QString(m->className()).startsWith("Q")) continue;
    //                         LOG_DEBUG("=== {} === Parent: {}", m->className(), obj->parent ? obj->parent->metaObject()->className() : "NULL");
    //
    //                         for (int j = m->methodOffset(); j < m->methodOffset() + m->methodCount(); ++j) {
    //                             const QMetaMethod method = m->method(j);
    //
    //                             const char *typeLabel = nullptr;
    //                             switch (method.methodType()) {
    //                                 case QMetaMethod::Signal: typeLabel = "SIGNAL";
    //                                     break;
    //                                 case QMetaMethod::Slot: typeLabel = "SLOT  ";
    //                                     break;
    //                                 default: continue; // skip QMetaMethod::Method and Constructor
    //                             }
    //
    //                             LOG_DEBUG("  [{}] {}", typeLabel, method.methodSignature().constData());
    //                         }
    //                     }
    //
    //                     if (QString("CloUICommon::CVFSignOnWorker") == mo->className()) {
    //                         LOG_INFO("FOUND CloUICommon::CVFSignOnWorker");
    //                         test = c->sender;
    //                     } else if (QString("AuthenticationProcessor") == mo->className()) {
    //                         LOG_INFO("FOUND AuthenticationProcessor");
    //                         ap = c->sender;
    //                     }
    //
    //                     QString h = mo->className();
    //                     do {
    //                         mo = mo->superClass();
    //                         h.append(" ").append(mo->className());
    //                     } while (mo->superClass());
    //                     LOG_DEBUG(" --- {}", h.toStdString());
    //
    //                     break;
    //                 }
    //                 ++sigCount;
    //             }
    //         }
    //     }
    // });
    //
    // HooksManager::addBefore<static_cast<void(*)(QObject*, const QMetaObject*, int, void**)>(&QMetaObject::activate)>([&](const HookHandle& handle, QObject *sender, const QMetaObject *m, int local_signal_index, void **argv) {
    //     if (sender && m &&
    //         (!QString(sender->metaObject()->className()).startsWith("Q")
    //         || QString(sender->metaObject()->className()) == "QAction"
    //         || QString(sender->metaObject()->className()) == "QMenu")
    //         || QString(
    //             sender->metaObject()->className()).contains("Network")
    //             ) {
    //         const int absIdx = m->methodOffset() + local_signal_index;
    //         const QMetaMethod sig = sender->metaObject()->method(absIdx);
    //         const auto sigName = sig.methodSignature();
    //
    //         const QByteArray macroSig = QByteArray("2") + sigName;
    //         const auto modifiedSender = static_cast<Hack *>(sender);
    //         const auto numOfReceivers = modifiedSender->receivers(macroSig.constData());
    //
    //         if (numOfReceivers > 0 && sender->objectName() != "actionMove_Pattern") {
    //             LOG_DEBUG("emit  {}({})::{} receivers: {}",
    //                       sender->metaObject()->className(),
    //                       sender->objectName().toStdString(),
    //                       sigName.constData(), numOfReceivers);
    //         }
    //     }
    // });
    for (const auto extension: extensions) {
        extension->install();
    }
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