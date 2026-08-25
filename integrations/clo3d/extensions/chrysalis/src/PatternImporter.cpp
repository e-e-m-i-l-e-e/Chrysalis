#include "PatternImporter.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTemporaryFile>

#include "CLOAPIInterface.h"

#include "Pattern.h"

#include "Logging.h"
#define LOGGER_NAME "Pattern Importer"

using namespace CLO3D;
using namespace Chrysalis;

PatternImporter::PatternImporter(std::unique_ptr<Project> project): project_(std::move(project)) {}

void PatternImporter::import() const {
    static auto getPointObject = [](const CG::Point& point, const bool isCurved = false) {
        QJsonObject pointObject;
        pointObject["ID"] = QString::number(reinterpret_cast<std::size_t>(&point));
        QJsonObject position;
        position["x"] = point.x() * 100;
        position["y"] = point.y() * 100;
        pointObject["Position"] = std::move(position);
        if (isCurved) pointObject["PointType"] = "Polyline";
        return pointObject;
    };
    LOG_INFO("Importing pattern from project: {}", project_->getName());
    project_->getInstructions()->run();

    QJsonObject root;
    QJsonArray patternList;
    const auto space = project_->getSpace();
    for (const auto& pattern: *project_->getPatterns()) {
        for (const auto patternSpace = pattern->getSpace();
             const auto& outline: *patternSpace->getOutline()) {
            QJsonObject patternObject;
            patternObject["Name"] = QString("%1 - %2")
                                    .arg(pattern->getName().data())
                                    .arg(outline->getName().data());
            QJsonArray lineList;
            QJsonObject prevPointObject;
            const Point* prevPoint = nullptr;
            for (const auto& point: outline->points()) {
                QJsonObject pointObject = getPointObject(*point);

                if (!prevPointObject.empty()) {
                    QJsonArray pointList;
                    pointList.push_back(prevPointObject);
                    if (space->hasCurve(point, prevPoint)) {
                        for (const auto curvePoint: space->getCurve(point, prevPoint)->curvePoints(0.1)) {
                            pointList.push_back(getPointObject(curvePoint, true));
                        }
                    }
                    pointList.push_back(pointObject);
                    QJsonObject lineObject;
                    lineObject["PointList"] = std::move(pointList);
                    lineList.push_back(std::move(lineObject));
                }

                prevPointObject = std::move(pointObject);
                prevPoint = point;
            }
            QJsonObject shapeInfo;
            shapeInfo["LineList"] = std::move(lineList);
            patternObject["ShapeInfo"] = std::move(shapeInfo);
            patternList.push_back(patternObject);
        }
    }

    root["PatternList"] = patternList;

    QTemporaryFile tempFile;
    if (!tempFile.open()) {
        LOG_ERROR("Failed to create temporary file.");
        return;
    }

    const QJsonDocument doc(root);
    tempFile.write(doc.toJson(QJsonDocument::Indented));
    tempFile.flush();

    if (std::string tempFilePath = tempFile.fileName().toStdString();
        !PATTERN_API->ImportPatternJSON(tempFilePath)) {
        LOG_ERROR("Failed to import pattern: {}", tempFilePath);
    }
}
