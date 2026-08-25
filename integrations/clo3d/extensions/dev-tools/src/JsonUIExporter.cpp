#include "JsonUIExporter.h"

#include <memory>
#include <utility>

#include <QLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <QApplication>
#include <QMetaProperty>
#include <QJsonDocument>

#include "ExtensionsManager.h"

#include "Logging.h"
#define LOGGER_NAME "Json UI Exporter"

using namespace CLO3D;

JsonUIExporter::JsonUIExporter(std::unique_ptr<JsonUIExporterOptions> options): options_(std::move(options)) {
    LOG_TRACE("Exporter has been created.");
}

JsonUIExporter* JsonUIExporter::create() {
    return new JsonUIExporter(std::make_unique<JsonUIExporterOptions>());
}

void JsonUIExporter::exportUI(std::forward_list<QWidget*>&& widgets) {
    QJsonArray json;
    for (const auto& widget : widgets) {
        if (const auto jsonObject = getWidgetJson(widget); !jsonObject.keys().isEmpty()) json.append(jsonObject);
    }

    const auto filePath = options_->getRootFolder().filePath(options_->getFileName().append(".json"));
    LOG_UI_MESSAGE(QString("Saving json data into %1").arg(filePath));

    if (QFile file(filePath); file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.write(QJsonDocument(json).toJson(QJsonDocument::Indented));
        file.close();
        LOG_UI_MESSAGE("Json data have been exported successfully.");
    } else {
        LOG_ERROR("Failed to open {} for writing: {}", filePath.toStdString(), file.errorString().toStdString());
    }
}

BaseUIExporterOptions* JsonUIExporter::getOptions() {
    return options_.get();
}

QJsonObject JsonUIExporter::getWidgetJson(const QWidget *widget) {
    if (options_->getVisibleOnly() && !widget->isVisible()) return {};

    UI_MESSAGE(
        QString("Exporting widget of class \"%1\" and object name \"%2\"")
        .arg(widget->metaObject()->className())
        .arg(widget->objectName())
    );

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
    if (!options_->getIgnoreCSS()) state["styleSheet"] = widget->styleSheet(); // direct — not inherited

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
            if (QJsonObject childWidgetJson = getWidgetJson(childWidget);
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
QJsonObject JsonUIExporter::getObjectJson(const QObject *object) {
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
                break;
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
