#include "XmlUIExporter.h"

#include <memory>
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
#include "Task.h"
#include "TaskGroup.h"
#define LOGGER_NAME "XML UI Exporter"

using namespace CLO3D;

XmlUIExporter::XmlUIExporter(std::unique_ptr<XmlUIExporterOptions> options): options_(std::move(options)) {
    LOG_TRACE("Exporter has been created.");
}

XmlUIExporter* XmlUIExporter::create() {
    return new XmlUIExporter(std::make_unique<XmlUIExporterOptions>());
}

void XmlUIExporter::exportUI(std::forward_list<QWidget*>&& widgets) {
    auto group = std::make_unique<TaskGroup>(EXPORT_TASK_NAME);
    int id = 0;
    for (const auto widget: widgets) {
        QByteArray buffer;
        {
            QFormBuilder builder;
            QBuffer device(&buffer);
            device.open(QIODevice::WriteOnly);
            builder.save(&device, widget);
            device.close();
        }
        ++id;
        group->addTask(std::make_unique<Task>(QString("Export widget #%1").arg(QString::number(id)), [this, id = QString::number(id), widget, buffer = std::move(buffer)] -> void {
            LOG_UI_MESSAGE(QString("#%1: Post processing XML of the widget with class name \"%2\" and object name \"%3\" "
                                   "in the background.")
                               .arg(id)
                               .arg(widget->metaObject()->className())
                               .arg(widget->objectName()));

            QString extension = "xml";
            QDomDocument doc;
            doc.setContent(buffer);
            if (options_->getUICompatible()) {
                extension = "ui";
                const auto isCustomClass = [](const QString& className) {
                    return !className.startsWith("Q");
                };

                const auto xml = doc.documentElement();
                const auto customWidgets = xml.toElement().appendChild(doc.createElement("customwidgets"));

                QStringList discoveredCustomWidgets;

                static constexpr auto LOG_POST_PROCESSING = FMT_STRING("#{}: Post-processing {}.");
                static constexpr auto LOG_POST_PROCESSING_PROGRESS = "#%1: Post-processing %2 %3 / %4.";

                LOG_INFO(LOG_POST_PROCESSING, id.toStdString(), "XML widgets");

                const auto widgetsXML = doc.elementsByTagName("widget");
                for (int i = widgetsXML.count() - 1; i >= 0; i--) {
                    UI_MESSAGE(QString(LOG_POST_PROCESSING_PROGRESS)
                                   .arg(id)
                                   .arg("XML widgets")
                                   .arg(QString::number(widgetsXML.count() - i))
                                   .arg(QString::number(widgetsXML.count())));

                    const auto widgetElement = widgetsXML.at(i).toElement();
                    const auto className = widgetElement.attribute("class");

                    // Delete internal Qt classes
                    static const QStringList CLASSES_TO_DELETE = {
                        "QHeaderView", "QTableCornerButton", "QComboBoxPrivateContainer"};
                    if (CLASSES_TO_DELETE.contains(className)) {
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
                            LOG_UI_MESSAGE(QString("#%1: Register custom widget of class \"%2\".").arg(id).arg(className));

                            discoveredCustomWidgets.append(className);

                            QStringList classNameList = QString(currentClass->className()).split("::");
                            QStringList locations;
                            for (int j = 0; j < classNameList.count() - 1; j++) {
                                QString location;
                                for (int k = 0; k < classNameList[j].length(); k++) {
                                    if (k > 0 && classNameList[j][k].isUpper() &&
                                        (classNameList[j][k - 1].isLower() || k == classNameList[j].length() - 1 ||
                                         classNameList[j][k + 1].isLower())) {
                                        location.append("-").append(classNameList[j][k].toLower());
                                    }
                                    else location.append(classNameList[j][k].toLower());
                                }
                                locations.append(location);
                            }
                            locations.append(classNameList.last());

                            auto customWidget =
                                customWidgets.toElement().appendChild(doc.createElement("customwidget")).toElement();

                            customWidget.appendChild(doc.createElement("class"))
                                .toElement()
                                .appendChild(doc.createTextNode(currentClass->className()));

                            customWidget.appendChild(doc.createElement("extends"))
                                .toElement()
                                .appendChild(doc.createTextNode(currentClass->superClass()->className()));

                            customWidget.appendChild(doc.createElement("header"))
                                .toElement()
                                .appendChild(doc.createTextNode(locations.join("/").append(".h")));

                            currentClass = currentClass->superClass();
                        }
                        while (isCustomClass(currentClass->className()));
                    }
                }

                LOG_INFO(LOG_POST_PROCESSING, id.toStdString(), "layouts");

                const auto layouts = doc.elementsByTagName("layout");
                for (int i = layouts.count() - 1; i >= 0; i--) {
                    UI_MESSAGE(QString(LOG_POST_PROCESSING_PROGRESS)
                                   .arg(id)
                                   .arg("layouts")
                                   .arg(QString::number(layouts.count() - i))
                                   .arg(QString::number(layouts.count())));

                    static const QStringList LAYOUTS_TO_TRANSFORM = {"QDockWidgetLayout", "QStackedLayout"};
                    if (const auto layoutElement = layouts.at(i).toElement();
                        LAYOUTS_TO_TRANSFORM.contains(layoutElement.attribute("class"))) {
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

                LOG_INFO(LOG_POST_PROCESSING, id.toStdString(), "properties");

                QSet<QString> resources;
                const auto properties = doc.elementsByTagName("property");
                for (int i = properties.count() - 1; i >= 0; i--) {
                    UI_MESSAGE(QString(LOG_POST_PROCESSING_PROGRESS)
                                   .arg(id)
                                   .arg("properties")
                                   .arg(QString::number(properties.count() - i))
                                   .arg(QString::number(properties.count())));

                    const auto property = properties.at(i).toElement();

                    // Find resources
                    if (options_->getExportIcons() &&
                        QStringList({"styleSheet", "text"}).contains(property.attribute("name"))) {
                        auto it = QRegularExpression(R"((:/[^"')<>]+\.svg))").globalMatch(property.text());
                        while (it.hasNext()) {
                            resources << it.next().captured(1);
                        }
                    }

                    if (property.attribute("name") == "objectName") {
                        const auto value = property.firstChildElement().text();

                        static const QStringList OBJECTS_TO_DELETE = {
                            "qt_scrollarea_vcontainer", "qt_scrollarea_hcontainer"};
                        if (OBJECTS_TO_DELETE.contains(value)) {
                            // Delete internal Qt widgets by object name
                            property.parentNode().parentNode().removeChild(property.parentNode());
                            continue;
                        }

                        if (value == "qt_scrollarea_viewport") {
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

                if (options_->getExportIcons()) {

                    static constexpr auto LOG_EXPORTING_RESOURCES = FMT_STRING("#{}: Exporting resources.");
                    static constexpr auto LOG_EXPORTING_RESOURCES_PROGRESS = "#%1: Exporting resources %2 / %3.";

                    LOG_INFO(LOG_EXPORTING_RESOURCES, id.toStdString());

                    static const QString RESOURCES_FOLDER_NAME = "resources";
                    auto resourcesDirectory = options_->getRootFolder();

                    if (resourcesDirectory.mkdir(RESOURCES_FOLDER_NAME)) {
                        LOG_INFO(Logging::Message::LOG_FOLDER_WAS_CREATED_IN_DIRECTORY,
                                 RESOURCES_FOLDER_NAME.toStdString(),
                                 resourcesDirectory.path().toStdString());
                    }
                    resourcesDirectory.cd(RESOURCES_FOLDER_NAME);

                    int i = 1;
                    for (auto resource: resources) {
                        UI_MESSAGE(QString(LOG_EXPORTING_RESOURCES_PROGRESS)
                                       .arg(id)
                                       .arg(QString::number(i))
                                       .arg(QString::number(resources.count())));

                        if (QFile in(resource); in.open(QIODevice::ReadOnly)) {
                            QString fullPath =
                                resourcesDirectory.filePath(resourcesDirectory.filePath(resource.remove(":/")));
                            if (QFileInfo info(fullPath); !QDir().mkpath(info.path())) {
                                LOG_ERROR(Logging::Message::LOG_FAILED_TO_CREATE_PATH, fullPath.toStdString());
                                continue;
                            }
                            if (QFile out(fullPath); out.open(QIODevice::WriteOnly)) {
                                out.write(in.readAll());
                            }
                            else {
                                LOG_ERROR(Logging::Message::LOG_FAILED_TO_OPEN_FILE, fullPath.toStdString());
                                continue;
                            }
                        }
                        else {
                            LOG_ERROR(Logging::Message::LOG_FAILED_TO_OPEN_FILE, resource.toStdString());
                            continue;
                        }
                        i++;
                    }
                }
            }

            if (options_->getExportIcons()) {
                LOG_INFO("#{}: Exporting tool buttons.", id.toStdString());

                QList<QToolButton*> buttons = widget->findChildren<QToolButton*>();

                static QString ICONS_FOLDER_NAME = "icons";
                QDir iconsDirectory = options_->getRootFolder();
                if (iconsDirectory.mkdir(ICONS_FOLDER_NAME)) {
                    LOG_INFO(Logging::Message::LOG_FOLDER_WAS_CREATED_IN_DIRECTORY,
                             ICONS_FOLDER_NAME.toStdString(),
                             options_->getRootFolder().path().toStdString());
                }
                iconsDirectory.cd(ICONS_FOLDER_NAME);

                int counter = 0;
                QSet<QByteArray> seenHashes;
                for (QToolButton* btn: buttons) {
                    QIcon icon = btn->icon();

                    static constexpr auto LOG_NO_IMAGE_FOR_ICON = "#%1: There is no image for icon. Skipping %2 / %3.";
                    static constexpr auto LOG_DUPLICATED_ICON = "#%1: Duplicate detected for icon. Skipping %2 / %3.";
                    static constexpr auto LOG_ICON_PROGRESS = "#%1: Exporting icon %2 / %3.";

                    if (icon.isNull()) {
                        UI_MESSAGE(QString(LOG_NO_IMAGE_FOR_ICON)
                                       .arg(id)
                                       .arg(QString::number(counter))
                                       .arg(QString::number(buttons.count())));
                        continue;
                    }

                    QSize size = btn->iconSize().isValid() ? btn->iconSize() : QSize(32, 32);
                    QPixmap pixmap = icon.pixmap(size);
                    if (pixmap.isNull()) {
                        UI_MESSAGE(QString(LOG_NO_IMAGE_FOR_ICON)
                                       .arg(id)
                                       .arg(QString::number(counter))
                                       .arg(QString::number(buttons.count())));
                        continue;
                    }

                    QImage image = pixmap.toImage();

                    QByteArray bytes(
                        reinterpret_cast<const char*>(image.constBits()), static_cast<int>(image.sizeInBytes()));
                    QByteArray hash = QCryptographicHash::hash(bytes, QCryptographicHash::Md5);

                    // Skip duplicates
                    if (seenHashes.contains(hash)) {
                        UI_MESSAGE(QString(LOG_DUPLICATED_ICON)
                                       .arg(id)
                                       .arg(QString::number(counter).arg(QString::number(buttons.count()))));
                        continue;
                    }

                    UI_MESSAGE(QString(LOG_ICON_PROGRESS)
                                   .arg(id)
                                   .arg(QString::number(counter))
                                   .arg(QString::number(buttons.count())));

                    seenHashes.insert(hash);

                    if (const auto iconPath =
                            iconsDirectory.filePath(QString("%1-%2").arg(id).arg(QString::number(counter++)))
                                .append(".png");
                        !pixmap.save(iconPath)) {
                        LOG_ERROR(Logging::Message::LOG_FAILED_TO_SAVE_FILE, iconPath.toStdString());
                    }
                }
            }

            LOG_UI_MESSAGE(QString("#%1: Saving XML file.").arg(id));
            const QString filePath = options_->getRootFolder().filePath(
                options_->getFileName().append("-").append(id).append(".").append(extension));
            if (QFile file(filePath); file.open(QIODevice::WriteOnly)) {
                QTextStream stream(&file);
                doc.save(stream, 4);
                file.close();
            }
            else {
                LOG_ERROR(Logging::Message::LOG_FAILED_TO_OPEN_FILE, filePath.toStdString());
            }
        }));
    }
    ExtensionsManager::executor.submit(std::move(group), [] -> void {
        ExtensionsManager::clearMessage();
    });
}

BaseUIExporterOptions* XmlUIExporter::getOptions() {
    return options_.get();
}
