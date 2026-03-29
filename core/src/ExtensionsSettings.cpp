#include "ExtensionsSettings.h"
#include "ui_ExtensionsSettings.h"

#define LOGGER_NAME "Extensions Settings"

#include <QComboBox>
#include <QDomDocument>
#include <qevent.h>
#include <QFileDialog>
#include <QFormBuilder>
#include <QtConcurrent>

#include "Logger.h"
#include "ExtensionsManager.h"

// Declarations of helpers ---------------------------------------------------------------------------------------------
QStringList logLevels;
QJsonObject getWidgetJson(const QWidget* widget, bool visibleOnly, bool ignoreCSS);
// ---------------------------------------------------------------------------------------------------------------------

// Shortcut ------------------------------------------------------------------------------------------------------------
ExtensionsSettings::Shortcut::Shortcut(ExtensionsSettings *parent)
    : QObject(parent),
      messageHook(SetWindowsHookEx(
              WH_GETMESSAGE,
              &Shortcut::trigger,
              nullptr,
              GetCurrentThreadId())) {}

ExtensionsSettings::Shortcut::~Shortcut() {
    if (messageHook) UnhookWindowsHookEx(messageHook);
    UnregisterHotKey(nullptr, 1);
}

bool ExtensionsSettings::Shortcut::registerShortcut(QLineEdit* shortcutLineEdit) const {
    QStringList parts;

    if (modifiers & MOD_CONTROL) parts << "Ctrl";
    if (modifiers & MOD_SHIFT)   parts << "Shift";
    if (modifiers & MOD_ALT)     parts << "Alt";
    if (modifiers & MOD_WIN)     parts << "Win";

    parts << QChar(key);

    shortcutLineEdit->setText(parts.join("+"));
    UnregisterHotKey(nullptr, 1);
    if (const bool ok = RegisterHotKey(nullptr, 1, modifiers, key); !ok) {
        LOG_ERROR("Shortcut registration failed: {}", GetLastError());
        return false;
    }
    return true;
}

bool ExtensionsSettings::Shortcut::eventFilter(QObject *watched, QEvent *event) {
    const auto shortcutLineEdit = qobject_cast<QLineEdit*>(watched);

    if (event->type() == QEvent::KeyPress) {
        const auto *keyEvent = dynamic_cast<QKeyEvent*>(event);
        const auto mods = keyEvent->modifiers();

        UINT result = 0;

        if (mods & Qt::ControlModifier) result |= MOD_CONTROL;
        if (mods & Qt::ShiftModifier)   result |= MOD_SHIFT;
        if (mods & Qt::AltModifier)     result |= MOD_ALT;
        if (mods & Qt::MetaModifier)    result |= MOD_WIN;

        // Ignore pure modifier keys
        if (keyEvent->key() == Qt::Key_Control ||
            keyEvent->key() == Qt::Key_Shift ||
            keyEvent->key() == Qt::Key_Alt ||
            keyEvent->key() == Qt::Key_Meta) {
            return true;
        }

        modifiers = result;
        key = keyEvent->nativeVirtualKey();
        return registerShortcut(shortcutLineEdit);
    }

    return QObject::eventFilter(watched, event);
}

LRESULT ExtensionsSettings::Shortcut::trigger(const int nCode, const WPARAM wParam, const LPARAM lParam) {
    if (nCode == HC_ACTION) {
        if (const auto msg = reinterpret_cast<MSG*>(lParam); msg->message == WM_HOTKEY && msg->wParam == 1) {
            ExtensionsManager::extensionsSettings->exportUI();
        }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}
// ---------------------------------------------------------------------------------------------------------------------

// Extensions Settings -------------------------------------------------------------------------------------------------
ExtensionsSettings::ExtensionsSettings(QWidget *parent) : MVDialog(parent),
                                                          ui(new Ui::ExtensionsSettings),
                                                          settings("eemilee.me", "CLO Extensions"),
                                                          shortcut(this) {

    LOG_INFO("Setting up \"Extensions Settings\"");

    // Set styles ------------------------------------------------------------------------------------------------------

    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);

    for (int i = 0; i < ui->stackedWidget->count(); i++) {
        UTILITY_API->UpdateCloStyleForPlugIn(ui->stackedWidget->widget(i));
    }

    UTILITY_API->UpdateCloStyleForPlugIn(ui->tableWidget);

    // Fill settings ---------------------------------------------------------------------------------------------------

    loadSettings();

    const auto connectFolderButton = [this](const QToolButton* button, QLineEdit* folderName) {
        connect(button, &QToolButton::clicked, this, [this, folderName] {
            const auto dir = QFileDialog::getExistingDirectory(
                this,
                "Select Folder",
                folderName->text(),
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
            );

            if (!dir.isEmpty()) {
                folderName->setText(dir);
            } else {
                LOG_ERROR("Failed to choose root folder.");
            }
        });
    };
    connectFolderButton(ui->generalFolderButton, ui->generalRootFolder);
    connectFolderButton(ui->jsonFolderButton, ui->jsonRootFolder);
    connectFolderButton(ui->xmlFolderButton, ui->xmlRootFolder);

    connect(ui->closeButton, &QToolButton::clicked, this, &ExtensionsSettings::saveSettings);
    connect(ui->resetButton, &QToolButton::clicked, this, &ExtensionsSettings::resetSettings);

    for (const auto button : findChildren<QAbstractButton*>()) {
        connect(button, &QAbstractButton::clicked, button, &QAbstractButton::clearFocus);
    }

    ui->shortcut->installEventFilter(&shortcut);
    shortcut.registerShortcut(ui->shortcut);

    // Configure loggers table ----------------------------------------------------------------------------------------------

    for (int i = 0; i < static_cast<int>(spdlog::level::n_levels); ++i) {
        auto sv = spdlog::level::to_string_view(static_cast<spdlog::level::level_enum>(i));
        logLevels << QString::fromUtf8(sv.data(), static_cast<int>(sv.size())).toUpper();
    }
}

ExtensionsSettings::~ExtensionsSettings() {
    delete ui;
}

void ExtensionsSettings::loadSettings() {
    const auto loadCommonSettings = [&](QLineEdit *rootFolder,
                                        QLineEdit *fileName,
                                        QLineEdit *className,
                                        QLineEdit *objectName) {
        if (settings.contains(Key::ROOT_FOLDER)) rootFolder->setText(settings.value(Key::ROOT_FOLDER).toString());
        else ui->generalRootFolder->setText(Key::DEFAULT_ROOT_FOLDER);

        if (settings.contains(Key::FILE_NAME)) fileName->setText(settings.value(Key::FILE_NAME).toString());

        className->setText(settings.value(Key::CLASS_NAME).toString());
        objectName->setText(settings.value(Key::OBJECT_NAME).toString());
    };

    settings.beginGroup(Key::UI_EXPORTER);

    settings.beginGroup(Key::GENERAL);
    loadCommonSettings(ui->generalRootFolder, ui->generalFileName, ui->generalClassName, ui->generalObjectName);
    settings.beginGroup(Key::SHORTCUT);
    if (settings.contains(Key::SHORTCUT_MODIFIERS)) shortcut.modifiers = settings.value(Key::SHORTCUT_MODIFIERS).toUInt();
    if (settings.contains(Key::SHORTCUT_KEY)) shortcut.key = settings.value(Key::SHORTCUT_KEY).toUInt();
    settings.endGroup();
    settings.endGroup();

    settings.beginGroup(Key::Json::JSON);
    if (settings.contains(Key::ENABLED)) ui->jsonEnabled->setChecked(settings.value(Key::ENABLED).toBool());
    loadCommonSettings(ui->jsonRootFolder, ui->jsonFileName, ui->jsonClassName, ui->jsonObjectName);
    if (settings.contains(Key::Json::VISIBLE_ONLY)) ui->visibleOnly->setChecked(settings.value(Key::Json::VISIBLE_ONLY).toBool());
    if (settings.contains(Key::Json::IGNORE_CSS)) ui->ignoreCSS->setChecked(settings.value(Key::Json::IGNORE_CSS).toBool());
    settings.endGroup();

    settings.beginGroup(Key::XML::Xml);
    if (settings.contains(Key::ENABLED)) ui->xmlEnabled->setChecked(settings.value(Key::ENABLED).toBool());
    loadCommonSettings(ui->xmlRootFolder, ui->xmlFileName, ui->xmlClassName, ui->xmlObjectName);
    if (settings.contains(Key::XML::EXPORT_ICONS)) ui->exportIcons->setChecked(settings.value(Key::XML::EXPORT_ICONS).toBool());
    if (settings.contains(Key::XML::UI_COMPATIBLE)) ui->uiCompatible->setChecked(settings.value(Key::XML::UI_COMPATIBLE).toBool());
    settings.endGroup();

    settings.endGroup();
}

void ExtensionsSettings::saveSettings() {
    const auto setCommonSettings = [&](const QLineEdit *rootFolder,
                                       const QLineEdit *fileName,
                                       const QLineEdit *className,
                                       const QLineEdit *objectName) {
        settings.setValue(Key::ROOT_FOLDER, rootFolder->text());
        settings.setValue(Key::FILE_NAME, fileName->text());
        settings.setValue(Key::CLASS_NAME, className->text());
        settings.setValue(Key::OBJECT_NAME, objectName->text());
    };

    settings.beginGroup(Key::UI_EXPORTER);

    settings.beginGroup(Key::GENERAL);
    setCommonSettings(ui->generalRootFolder, ui->generalFileName, ui->generalClassName, ui->generalObjectName);
    settings.beginGroup(Key::SHORTCUT);
    settings.setValue(Key::SHORTCUT_MODIFIERS, shortcut.modifiers);
    settings.setValue(Key::SHORTCUT_KEY, shortcut.key);
    settings.endGroup();
    settings.endGroup();

    settings.beginGroup(Key::Json::JSON);
    settings.setValue(Key::ENABLED, ui->jsonEnabled->isChecked());
    setCommonSettings(ui->jsonRootFolder, ui->jsonFileName, ui->jsonClassName, ui->jsonObjectName);
    settings.setValue(Key::Json::VISIBLE_ONLY, ui->visibleOnly->isChecked());
    settings.setValue(Key::Json::IGNORE_CSS, ui->ignoreCSS->isChecked());
    settings.endGroup();

    settings.beginGroup(Key::XML::Xml);
    settings.setValue(Key::ENABLED, ui->xmlEnabled->isChecked());
    setCommonSettings(ui->xmlRootFolder, ui->xmlFileName, ui->xmlClassName, ui->xmlObjectName);
    settings.setValue(Key::XML::EXPORT_ICONS, ui->exportIcons->isChecked());
    settings.setValue(Key::XML::UI_COMPATIBLE, ui->uiCompatible->isChecked());
    settings.endGroup();

    settings.endGroup();

    LOG_DEBUG("Settings have been saved.");
}

void ExtensionsSettings::resetSettings() {
    ui->generalRootFolder->setText(Key::DEFAULT_ROOT_FOLDER);
    ui->generalFileName->setText(Key::DEFAULT_FILE_NAME);
    ui->generalClassName->setText("");
    ui->generalObjectName->setText("");

    shortcut.modifiers = Key::DEFAULT_MODIFIERS;
    shortcut.key = Key::DEFAULT_KEY;
    shortcut.registerShortcut(ui->shortcut);

    ui->jsonEnabled->setChecked(true);
    ui->visibleOnly->setChecked(true);
    ui->ignoreCSS->setChecked(true);

    ui->xmlEnabled->setChecked(true);
    ui->exportIcons->setChecked(true);
    ui->uiCompatible->setChecked(true);
}

void ExtensionsSettings::showEvent(QShowEvent *event) {
    while (ui->tableWidget->rowCount() > 0) ui->tableWidget->removeRow(0);
    for (const auto logger: Logger::getAll()) {
        LOG_DEBUG("\"{}\" logger has been detected.", logger->name());

        ui->tableWidget->insertRow(0);

        // Logger name
        auto *nameItem = new QTableWidgetItem(QString::fromStdString(logger->name()));
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(0, 0, nameItem);

        // Logger level
        auto *combo = new QComboBox(ui->tableWidget);
        combo->addItems(logLevels);
        combo->setCurrentIndex(logger->level());
        ui->tableWidget->setCellWidget(0, 1, combo);

        // Apply level change immediately when the user picks a new entry
        connect(combo, qOverload<int>(&QComboBox::currentIndexChanged), this, [logger](int index) {
            logger->setLevel(static_cast<spdlog::level::level_enum>(index));
        });
    }
    // Synthesize a Leave event on every button so Qt's style engine resets the
    // frozen hover state that persists when the window was hidden rather than
    // the mouse physically leaving the widget.
    for (const auto button: findChildren<QAbstractButton *>()) QApplication::postEvent(
        button, new QEvent(QEvent::Leave));
    QDialog::showEvent(event);
}

void ExtensionsSettings::exportUI() const {

    if (ui->shortcut->hasFocus()) {
        LOG_DEBUG("Skipping UI export. Shortcut field is focused.");
        return;
    }

    if (ui->jsonEnabled->isChecked()) exportJson();
    if (ui->xmlEnabled->isChecked()) exportXML();
    else ExtensionsManager::clearMessage();
}

void ExtensionsSettings::exportJson() const {

    LOG_UI_MESSAGE("Exporting UI in json format.");

    const auto className = ui->jsonClassName->text();
    const auto objectName = ui->jsonObjectName->text();
    const auto visibleOnly = ui->visibleOnly->isChecked();
    const auto ignoreCSS = ui->ignoreCSS->isChecked();

    QJsonArray root;
    if (className.isEmpty() && objectName.isEmpty()) {
        // Export everything
        for (const auto widget: QApplication::topLevelWidgets()) {
            if (!widget->parent()) {
                if (const auto object = getWidgetJson(widget, visibleOnly, ignoreCSS);
                    !object.keys().empty()) {
                    root.append(object);
                }
            }
        }
    } else {
        // Find widget by parameters
        for (const auto widget: QApplication::allWidgets()) {
            if ((objectName.isEmpty() || objectName == widget->objectName()) &&
                (className.isEmpty() || className == widget->metaObject()->className())) {
                LOG_DEBUG(
                    "Matching widget has been found with class \"{}\" and name \"{}\"",
                    widget->objectName().toStdString(),
                    widget->metaObject()->className()
                );
                if (const auto object = getWidgetJson(widget, visibleOnly, ignoreCSS);
                    !object.keys().empty()) {
                    root.append(object);
                }
            }
        }
    }

    // ── Write file ────────────────────────────────────────────────────────

    const auto filePath = QString(ui->jsonRootFolder->text()).append("/").append(ui->jsonFileName->text()).append(".json");

    LOG_UI_MESSAGE(QString("Saving json data into %1").arg(filePath));

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        LOG_ERROR("Failed to open {} for writing: {}", filePath.toStdString(), file.errorString().toStdString());
        return;
    }

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();

    LOG_UI_MESSAGE("Json data have been exported successfully.");
}

void ExtensionsSettings::exportXML() const {

    LOG_UI_MESSAGE("Exporting UI in xml format.");

    QWidget* widget = ExtensionsManager::mainWindow;
    if (const auto objectName = ui->xmlObjectName->text(), className = ui->xmlClassName->text();
        !className.isEmpty() || !objectName.isEmpty()) {
        for (const auto w: QApplication::allWidgets()) {
            if ((objectName.isEmpty() || objectName == w->objectName()) &&
                (className.isEmpty() || className == w->metaObject()->className())) {
                LOG_DEBUG(
                    "Matching widget has been found with class \"{}\" and name \"{}\"",
                    widget->objectName().toStdString(),
                    widget->metaObject()->className()
                );
                widget = w;
            }
        }
    }

    // Fill the buffer synchronously on the main thread before launching the worker.
    QByteArray buffer;
    {
        QFormBuilder builder;
        QBuffer device(&buffer);
        device.open(QIODevice::WriteOnly);
        builder.save(&device, widget);
        device.close();
    }

    const bool    uiCompatible = ui->uiCompatible->isChecked();
    const bool    exportIcons  = ui->exportIcons->isChecked();
    const QString rootFolder   = ui->xmlRootFolder->text();
    const QString fileName     = ui->xmlFileName->text();

    // Move the buffer into the lambda so the thread owns its lifetime.
    QtConcurrent::run([
        buffer = std::move(buffer),
        widget,
        uiCompatible,
        exportIcons,
        rootFolder,
        fileName
    ]() mutable {

        LOG_UI_MESSAGE("Post processing XML in the background.");

        QDomDocument doc;
        doc.setContent(buffer);

        if (uiCompatible) {
            const auto isCustomClass = [](const QString &className) {
                return !className.startsWith("Q");
            };

            const auto xml = doc.documentElement();
            const auto customWidgets = xml.toElement().appendChild(doc.createElement("customwidgets"));

            QStringList discoveredCustomWidgets;

            LOG_INFO("Post-processing XML widgets.");

            const auto widgets = doc.elementsByTagName("widget");
            for (int i = widgets.count() - 1; i >= 0; i--) {
                UI_MESSAGE(QString("Post-processing XML widgets %1 / %2.").arg(QString::number(widgets.count() - i)).arg(QString::number(widgets.count())));

                const auto widgetElement = widgets.at(i).toElement();
                const auto className = widgetElement.attribute("class");

                // Delete internal Qt classes
                if (QStringList({
                    "QHeaderView",
                    "QTableCornerButton",
                    "QComboBoxPrivateContainer"
                }).contains(className)) {
                    widgetElement.parentNode().removeChild(widgetElement);
                    continue;
                }

                // Register custom widgets
                if (isCustomClass(className) && !discoveredCustomWidgets.contains(className)) {
                    // Looking for widget of custom CLO class
                    const QMetaObject* currentClass = nullptr;
                    for (const auto w: QApplication::allWidgets()) {
                        if (QString(className) == w->metaObject()->className()) {
                            currentClass = w->metaObject();
                        }
                    }
                    do {
                        LOG_UI_MESSAGE("Register custom " + className + " widget.");

                        discoveredCustomWidgets.append(className);

                        QStringList classNameList = QString(currentClass->className()).split("::");
                        QStringList locations;
                        for (int j = 0; j < classNameList.count() - 1; j++) {
                            QString location;
                            for (int k = 0; k < classNameList[j].length(); k++) {
                                if (k > 0 && classNameList[j][k].isUpper() && (
                                        classNameList[j][k - 1].isLower() || k == classNameList[j].length() - 1 ||
                                        classNameList[j][k + 1].isLower())) {
                                    location.append("-").append(classNameList[j][k].toLower());
                                } else location.append(classNameList[j][k].toLower());
                            }
                            locations.append(location);
                        }
                        locations.append(classNameList.last());

                        auto customWidget = customWidgets.toElement()
                                .appendChild(doc.createElement("customwidget")).toElement();

                        customWidget
                                .appendChild(doc.createElement("class")).toElement()
                                .appendChild(doc.createTextNode(currentClass->className()));

                        customWidget
                                .appendChild(doc.createElement("extends")).toElement()
                                .appendChild(doc.createTextNode(currentClass->superClass()->className()));

                        customWidget
                                .appendChild(doc.createElement("header")).toElement()
                                .appendChild(doc.createTextNode(locations.join("/").append(".h")));

                        currentClass = currentClass->superClass();
                    } while (isCustomClass(currentClass->className()));
                }
            }

            LOG_INFO("Post-processing layouts.");

            const auto layouts = doc.elementsByTagName("layout");
            for (int i = layouts.count() - 1; i >= 0; i--) {

                UI_MESSAGE(QString("Post-processing layouts %1 / %2.").arg(QString::number(layouts.count() - i)).arg(QString::number(layouts.count())));

                if (const auto layoutElement = layouts.at(i).toElement();
                    QStringList({
                    "QDockWidgetLayout", "QStackedLayout"
                    }).contains(layoutElement.attribute("class"))) {
                    // Transform Qt internal layouts
                    const auto items = layoutElement.elementsByTagName("item");
                    while (!items.isEmpty()) {
                        // Move widgets from private QStackedLayout into QStackedWidget
                        const auto item = items.at(0).toElement();
                        item.parentNode().parentNode().appendChild(item.firstChildElement());
                        item.parentNode().removeChild(item);
                    }
                    // Delete internal layout
                    layoutElement.parentNode().removeChild(layoutElement);
                }
            }

            LOG_INFO("Post-processing properties.");

            QSet<QString> resources;
            const auto properties = doc.elementsByTagName("property");
            for (int i = properties.count() - 1; i >= 0; i--) {

                UI_MESSAGE(QString("Post-processing properties %1 / %2.").arg(QString::number(properties.count() - i)).arg(QString::number(properties.count())));

                const auto property = properties.at(i).toElement();

                // Find resources
                if (exportIcons && QStringList({"styleSheet", "text"}).contains(property.attribute("name"))) {
                    auto it = QRegularExpression(R"((:/[^"')<>]+\.svg))").globalMatch(property.text());
                    while (it.hasNext()) {
                        resources << it.next().captured(1);
                    }
                }

                if (property.attribute("name") == "objectName") {
                    const auto value = property.firstChildElement().text();

                    if (QStringList({
                        "qt_scrollarea_vcontainer",
                        "qt_scrollarea_hcontainer"
                    }).contains(value)) {
                        // Delete internal Qt widgets by object name
                        property.parentNode().parentNode().removeChild(property.parentNode());
                        continue;
                    }

                    if (QStringList({
                        "qt_scrollarea_viewport"
                    }).contains(value)) {
                        const auto childNodes = property.parentNode().childNodes();
                        for (int j = 0; j < childNodes.count(); j++) {
                            if (QStringList({"widget", "layout"}).contains(childNodes.at(j).toElement().tagName())) {
                                property.parentNode().parentNode().appendChild(childNodes.at(j));
                            }
                        }
                        property.parentNode().parentNode().removeChild(property.parentNode());
                    }
                }

                // Delete empty properties
                if (property.childNodes().length() != 1) continue;

                if ((property.firstChildElement().attributes().isEmpty() ||
                     property.firstChildElement().attributes().length() == 1 &&
                     property.firstChildElement().hasAttribute("notr")) &&
                    property.firstChildElement().childNodes().isEmpty()) {
                    property.parentNode().removeChild(property);
                }
            }

            LOG_INFO("Exporting resources.");

            const auto resourcesDirectory = QString(rootFolder).append("/resources/");

            int i = 1;
            for (auto resource: resources) {
                UI_MESSAGE(
                    QString("Exporting resources %1 / %2.").arg(QString::number(i).arg(QString::number(resources.count()
                    ))));

                QFile in(resource);
                if (!in.open(QIODevice::ReadOnly)) {
                    LOG_ERROR("Failed to open resource: \"{}\"", resource.toStdString());
                    continue;
                }

                QString fullPath(resourcesDirectory + resource.remove(":/"));

                if (const auto directory = QFileInfo(fullPath).path();
                    QDir().mkpath(directory)) {
                    QFile out(fullPath);
                    if (!out.open(QIODevice::WriteOnly)) {
                        LOG_ERROR("Failed to write file: {}", fullPath.toStdString());
                        continue;
                    }
                    out.write(in.readAll());
                } else {
                    LOG_ERROR("Failed to create directory: {}", directory.toStdString());
                }
                i++;
            }
        }

        if (exportIcons) {
            LOG_INFO("Exporting tool buttons.");

            QList<QToolButton*> buttons = widget->findChildren<QToolButton*>();

            if (const auto path = QString(rootFolder).append("/icons/");
                QDir().mkpath(path)) {
                int counter = 0;
                QSet<QByteArray> seenHashes;
                for (QToolButton *btn: buttons) {

                    QIcon icon = btn->icon();
                    if (icon.isNull()) {
                        UI_MESSAGE(QString("There is no image for icon. Skipping ").append(QString::number(counter).append(" / ").append(QString::number(buttons.count())).append(".")));
                        continue;
                    }

                    QSize size = btn->iconSize().isValid() ? btn->iconSize() : QSize(32, 32);
                    QPixmap pixmap = icon.pixmap(size);
                    if (pixmap.isNull()) {
                        UI_MESSAGE(QString("There is no image for icon. Skipping ").append(QString::number(counter).append(" / ").append(QString::number(buttons.count())).append(".")));
                        continue;
                    }

                    QImage image = pixmap.toImage();

                    QByteArray bytes(reinterpret_cast<const char*>(image.constBits()), image.sizeInBytes());
                    QByteArray hash = QCryptographicHash::hash(bytes, QCryptographicHash::Md5);

                    // Skip duplicates
                    if (seenHashes.contains(hash)) {
                        UI_MESSAGE(QString("Duplicate detected for icon. Skipping %1 / %2.").arg(QString::number(counter).arg(QString::number(buttons.count()))));
                        continue;
                    }

                    UI_MESSAGE(QString("Exporting icon %1 / %2.").arg(QString::number(counter).arg(QString::number(buttons.count()))));

                    seenHashes.insert(hash);

                    if (const auto iconPath = path + QString::number(counter++) + ".png"; !pixmap.save(iconPath)) {
                        LOG_ERROR("Failed to save icon: {}", iconPath.toStdString());
                    }
                }
            } else {
                LOG_ERROR("Failed to create path: {}", path.toStdString());
            }
        }

        LOG_UI_MESSAGE("Saving XML file.");

        QFile file(QString(rootFolder).append("/").append(fileName).append(".ui"));

        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        doc.save(stream, 4);
        file.close();

        ExtensionsManager::clearMessage();

        QMetaObject::invokeMethod(qApp, [] {
            UTILITY_API->DisplayMessageBox("UI data have been exported successfully.");
        });
    });
}
// ---------------------------------------------------------------------------------------------------------------------

// Helpers -------------------------------------------------------------------------------------------------------------
QJsonObject getObjectJson(const QObject *object) {

    const auto address = [](const QObject* widget) {
        return QString("0x%1").arg(reinterpret_cast<quintptr>(widget->parent()), 0, 16);
    };

    QJsonObject objectJson;

    // ── Identity ──────────────────────────────────────────────────────────
    objectJson["class"] = QString(object->metaObject()->className());

    QStringList classHierarchy;
    for (const QMetaObject* metaData = object->metaObject(); metaData != nullptr; metaData = metaData->superClass()) {
        classHierarchy.append(QString(metaData->className()));
    }

    objectJson["classHierarchy"] = classHierarchy.join(" -> ");
    objectJson["objectName"] = object->objectName();
    objectJson["address"] = address(object);

    if (object->parent()) {
        objectJson["parent"] = address(object->parent());
    }

    // ── Q_PROPERTY meta-properties ────────────────────────────────────────
    // Walk the full inheritance chain so properties defined on base classes
    // (e.g. QAbstractButton::text) are captured alongside derived ones.

    QJsonObject properties;

    const QMetaObject* meta = object->metaObject();
    for (int i = 0; i < meta->propertyCount(); ++i) {
        const QMetaProperty property = meta->property(i);
        const QVariant value     = property.read(object);

        if (!value.isValid() || value.isNull()) continue;

        switch (value.type()) {
            case QVariant::Bool: {
                properties[property.name()] = value.toBool();
            }
            case QVariant::Int:
            case QVariant::UInt:
            case QVariant::LongLong:
            case QVariant::ULongLong: {
                properties[property.name()] = value.toLongLong();
                break;
            }
            case QVariant::Double: {
                properties[property.name()] = value.toDouble();
                break;
            }
            case QVariant::String: {
                properties[property.name()] = value.toString();
                break;
            }
            case QVariant::ByteArray: {
                properties[property.name()] = QString(value.toByteArray().toHex());
                break;
            }
            case QVariant::Point: {
                const auto point = value.toPoint();
                properties[property.name()] = QString("(%1, %2)").arg(point.x()).arg(point.y());
                break;
            }
            case QVariant::Size: {
                const auto size = value.toSize();
                properties[property.name()] = QString("%1 x %2").arg(size.width()).arg(size.height());
                break;
            }
            case QVariant::Rect: {
                const auto rect = value.toRect();
                properties[property.name()] = QString("(%1, %2) %3 x %4")
                           .arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height());
                break;
            }
            case QVariant::Color: {
                properties[property.name()] = value.value<QColor>().name(QColor::HexArgb);
                break;
            }
            case QVariant::Font: {
                properties[property.name()] = value.value<QFont>().toString();
                break;
            }
            default: {
                // For everything else, fall back to Qt's own string conversion.
                // If that too fails, record the type name so it's not lost.
                const QString str = value.toString();
                properties[property.name()] = str.isEmpty()
                    ? QJsonValue(QString("<") + value.typeName() + ">")
                    : QJsonValue(str);
            }
        }
    }
    objectJson["properties"] = properties;

    return objectJson;
}
QJsonObject getWidgetJson(const QWidget* widget, const bool visibleOnly, const bool ignoreCSS) {

    if (visibleOnly && !widget->isVisible()) return {};

    UI_MESSAGE(QString("Exporting widget of class \"%1\" and object name \"%2\"").arg(widget->metaObject()->className()).arg(widget->objectName()));

    auto objectJson = getObjectJson(widget);

    // ── Geometry ──────────────────────────────────────────────────────────
    // mapToGlobal gives position in screen coordinates, independent of
    // scroll offsets or parent transforms — useful for visual reconstruction.
    const QRect local = widget->geometry();
    const QPoint global = widget->mapToGlobal(QPoint(0, 0));

    QJsonObject geometry;
    geometry["x"] = local.x();
    geometry["y"] = local.y();
    geometry["width"] = local.width();
    geometry["height"] = local.height();
    geometry["globalX"] = global.x();
    geometry["globalY"] = global.y();

    objectJson["geometry"] = geometry;

    // ── State ─────────────────────────────────────────────────────────────
    QJsonObject state;
    state["visible"] = widget->isVisible();
    state["enabled"] = widget->isEnabled();
    state["isWindow"] = widget->isWindow();
    state["isModal"] = widget->isModal();
    state["windowTitle"] = widget->windowTitle();
    state["toolTip"] = widget->toolTip();
    state["sizePolicy"] = QString("%1 / %2")
            .arg(widget->sizePolicy().horizontalPolicy())
            .arg(widget->sizePolicy().verticalPolicy());
    if (!ignoreCSS) state["styleSheet"] = widget->styleSheet(); // direct — not inherited

    objectJson["state"] = state;

    // ── Layout ────────────────────────────────────────────────────────────
    if (const QLayout *layout = widget->layout()) {
        QJsonObject layoutJson;

        layoutJson["class"]     = QString(layout->metaObject()->className());
        layoutJson["itemCount"] = layout->count();
        layoutJson["spacing"]   = layout->spacing();

        const QMargins m = layout->contentsMargins();
        QJsonObject margins;
        margins["left"]   = m.left();
        margins["top"]    = m.top();
        margins["right"]  = m.right();
        margins["bottom"] = m.bottom();
        layoutJson["margins"] = margins;

        objectJson["layout"] = layoutJson;
    }

    // ── Children ─────────────────────────────────────────────────────────
    // QObject::children() includes non-widget children (actions, models…).
    // We separate them so the consumer can choose what to inspect.
    QJsonArray widgets;
    QJsonArray objects;

    for (const auto child: widget->children()) {
        if (const auto childWidget = qobject_cast<QWidget*>(child)) {
            if (QJsonObject childWidgetJson = getWidgetJson(childWidget, visibleOnly, ignoreCSS);
                !childWidgetJson.keys().isEmpty()) {
                widgets.append(childWidgetJson);
            }
        } else {
            objects.append(getObjectJson(child));
        }
    }

    if (!widgets.isEmpty()) objectJson["widgets"] = widgets;
    if (!objects.isEmpty()) objectJson["objects"] = objects;

    return objectJson;
}
// ---------------------------------------------------------------------------------------------------------------------