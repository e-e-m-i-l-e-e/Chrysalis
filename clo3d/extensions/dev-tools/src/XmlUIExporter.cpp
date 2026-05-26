#include "XmlUIExporter.h"

#include <future>
#include <forward_list>

#include <QSet>
#include <QBuffer>
#include <QTextStream>
#include <QToolButton>
#include <QFormBuilder>
#include <QDomDocument>
#include <QApplication>
#include <QRegularExpression>
#include <QCryptographicHash>

#include "ExtensionsManager.h"

#include "Logging.h"
#define LOGGER_NAME "XML UI Exporter"

// TODO: Improve logging

XmlUIExporter::XmlUIExporter(XmlUIExporterOptions *options): options_(options) {}

XmlUIExporter::~XmlUIExporter() {
    delete options_;
}

void XmlUIExporter::exportUI(std::forward_list<QWidget*> widgets) {
    int id = 0;
    std::forward_list<std::future<void>> backgroundPostProcessors;
    for (const auto widget: widgets) {
        id++;
        // Fill the buffer synchronously on the main thread before launching the worker.
        QByteArray buffer;
        {
            QFormBuilder builder;
            QBuffer device(&buffer);
            device.open(QIODevice::WriteOnly);
            builder.save(&device, widget);
            device.close();
        }

        // Move the buffer into the lambda so the thread owns its lifetime.
        backgroundPostProcessors.push_front(std::async(std::launch::async,
        [this, id, buffer = std::move(buffer), widget]() mutable {
                LOG_UI_MESSAGE(
                    QString("#%1: Post processing XML of the widget with class name \"%2\" and object name \"%3\" in the background.")
                    .arg(QString::number(id))
                    .arg(widget->metaObject()->className())
                    .arg(widget->objectName())
                );

                QString extension = "xml";
                QDomDocument doc;
                doc.setContent(buffer);
                if (options_->getUICompatible()) {
                    extension = "ui";
                    const auto isCustomClass = [](const QString &className) {
                        return !className.startsWith("Q");
                    };

                    const auto xml = doc.documentElement();
                    const auto customWidgets = xml.toElement().appendChild(doc.createElement("customwidgets"));

                    QStringList discoveredCustomWidgets;

                    LOG_INFO("#{}: Post-processing XML widgets.", id);

                    const auto widgetsXML = doc.elementsByTagName("widget");
                    for (int i = widgetsXML.count() - 1; i >= 0; i--) {
                        UI_MESSAGE(
                            QString("#%1: Post-processing XML widgets %2 / %3.")
                            .arg(QString::number(id))
                            .arg(QString::number(widgetsXML.count() - i))
                            .arg(QString::number(widgetsXML.count()))
                        );

                        const auto widgetElement = widgetsXML.at(i).toElement();
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
                            const QMetaObject *currentClass = nullptr;
                            for (const auto w: QApplication::allWidgets()) {
                                if (QString(className) == w->metaObject()->className()) {
                                    currentClass = w->metaObject();
                                }
                            }
                            do {
                                LOG_UI_MESSAGE(
                                    QString("#%1: Register custom widget of class \"%2\".")
                                    .arg(id)
                                    .arg(className)
                                );

                                discoveredCustomWidgets.append(className);

                                QStringList classNameList = QString(currentClass->className()).split("::");
                                QStringList locations;
                                for (int j = 0; j < classNameList.count() - 1; j++) {
                                    QString location;
                                    for (int k = 0; k < classNameList[j].length(); k++) {
                                        if (k > 0 && classNameList[j][k].isUpper() && (
                                                classNameList[j][k - 1].isLower() || k == classNameList[j].length() - 1
                                                ||
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

                    LOG_INFO("#{}: Post-processing layouts.", id);

                    const auto layouts = doc.elementsByTagName("layout");
                    for (int i = layouts.count() - 1; i >= 0; i--) {
                        UI_MESSAGE(
                            QString("#%1: Post-processing layouts %2 / %3.")
                            .arg(QString::number(id))
                            .arg(QString::number(layouts.count() - i))
                            .arg(QString::number(layouts.count()))
                        );

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

                    LOG_INFO("#{}: Post-processing properties.", id);

                    QSet<QString> resources;
                    const auto properties = doc.elementsByTagName("property");
                    for (int i = properties.count() - 1; i >= 0; i--) {
                        UI_MESSAGE(
                            QString("#%1: Post-processing properties %2 / %3.")
                            .arg(QString::number(id))
                            .arg(QString::number(properties.count() - i))
                            .arg(QString::number(properties.count()))
                        );

                        const auto property = properties.at(i).toElement();

                        // Find resources
                        if (options_->getExportIcons() && QStringList({"styleSheet", "text"}).contains(property.attribute("name"))) {
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
                                    if (QStringList({"widget", "layout"}).contains(
                                        childNodes.at(j).toElement().tagName())) {
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

                    if (options_->getExportIcons()) {
                        LOG_INFO("#{}: Exporting resources.", id);

                        static QString RESOURCES_FOLDER_NAME = "resources";
                        auto resourcesDirectory = options_->getRootFolder();

                        if (resourcesDirectory.mkdir(RESOURCES_FOLDER_NAME)) {
                            LOG_INFO("\"{}\" folder has been created under {}.", RESOURCES_FOLDER_NAME.toStdString(), resourcesDirectory.path().toStdString());
                        }
                        resourcesDirectory.cd(RESOURCES_FOLDER_NAME);

                        int i = 1;
                        for (auto resource: resources) {
                            UI_MESSAGE(
                                QString("#%1: Exporting resources %2 / %3.")
                                .arg(QString::number(id))
                                .arg(QString::number(i))
                                .arg(QString::number(resources.count()))
                            );

                            if (QFile in(resource); in.open(QIODevice::ReadOnly)) {
                                QString fullPath = resourcesDirectory.filePath(resourcesDirectory.filePath(resource.remove(":/")));
                                if (QFileInfo info(fullPath); !QDir().mkpath(info.path())) {
                                    LOG_ERROR("Failed to create path for resource: {}", fullPath.toStdString());
                                    continue;
                                }
                                if (QFile out(fullPath); out.open(QIODevice::WriteOnly)) {
                                    out.write(in.readAll());
                                } else {
                                    LOG_ERROR("Failed to write file: {}", fullPath.toStdString());
                                    continue;
                                }
                            } else {
                                LOG_ERROR("Failed to open resource: \"{}\"", resource.toStdString());
                                continue;
                            }
                            i++;
                        }
                    }
                }

                if (options_->getExportIcons()) {
                    LOG_INFO("#{}: Exporting tool buttons.", id);

                    QList<QToolButton*> buttons = widget->findChildren<QToolButton*>();

                    static QString ICONS_FOLDER_NAME = "icons";
                    QDir iconsDirectory = options_->getRootFolder();
                    if (iconsDirectory.mkdir(ICONS_FOLDER_NAME)) {
                        LOG_INFO("\"{}\" folder was created under \"{}\" directory.", ICONS_FOLDER_NAME.toStdString(), options_->getRootFolder().path().toStdString());
                    }
                    iconsDirectory.cd(ICONS_FOLDER_NAME);

                    int counter = 0;
                    QSet<QByteArray> seenHashes;
                    for (QToolButton* btn: buttons) {
                        QIcon icon = btn->icon();
                        if (icon.isNull()) {
                            UI_MESSAGE(
                                QString("#%1: There is no image for icon. Skipping %2 / %3.")
                                .arg(QString::number(id))
                                .arg(QString::number(counter))
                                .arg(QString::number(buttons.count()))
                            );
                            continue;
                        }

                        QSize size = btn->iconSize().isValid() ? btn->iconSize() : QSize(32, 32);
                        QPixmap pixmap = icon.pixmap(size);
                        if (pixmap.isNull()) {
                            UI_MESSAGE(
                                QString("#%1: There is no image for icon. Skipping %2 / %3.")
                                .arg(QString::number(id))
                                .arg(QString::number(counter))
                                .arg(QString::number(buttons.count()))
                            );
                            continue;
                        }

                        QImage image = pixmap.toImage();

                        QByteArray bytes(
                            reinterpret_cast<const char*>(image.constBits()),
                            static_cast<int>(image.sizeInBytes())
                        );
                        QByteArray hash = QCryptographicHash::hash(bytes, QCryptographicHash::Md5);

                        // Skip duplicates
                        if (seenHashes.contains(hash)) {
                            UI_MESSAGE(
                                QString("#%1: Duplicate detected for icon. Skipping %2 / %3.")
                                .arg(QString::number(id))
                                .arg(QString::number(counter)
                                .arg(QString::number(buttons.count())))
                            );
                            continue;
                        }

                        UI_MESSAGE(
                            QString("#%1: Exporting icon %2 / %3.")
                            .arg(QString::number(id))
                            .arg(QString::number(counter))
                            .arg(QString::number(buttons.count()))
                        );

                        seenHashes.insert(hash);

                        if (const auto iconPath = iconsDirectory.filePath(QString("%1-%2").arg(QString::number(id)).arg(QString::number(counter++))).append(".png"); !pixmap.save(iconPath)) {
                            LOG_ERROR("Failed to save icon: {}", iconPath.toStdString());
                        }
                    }
                }

                LOG_UI_MESSAGE(QString("#%1: Saving XML file.").arg(id));
                QString filePath = options_->getRootFolder().filePath(options_->getFileName().append("-").append(QString::number(id)).append(".").append(extension));
                if (QFile file(filePath); file.open(QIODevice::WriteOnly)) {
                    QTextStream stream(&file);
                    doc.save(stream, 4);
                    file.close();
                } else {
                    LOG_ERROR("Failed to open file: {}", filePath.toStdString());
                }
            }
        ));
    }

    // Wait in another background thread
    std::thread([backgroundPostProcessors = std::move(backgroundPostProcessors)]() mutable{
        for (auto &future: backgroundPostProcessors) {
            future.get();
        }
        ExtensionsManager::clearMessage();
    }).detach();
}

BaseUIExporterOptions* XmlUIExporter::getOptions() {
    return options_;
}
