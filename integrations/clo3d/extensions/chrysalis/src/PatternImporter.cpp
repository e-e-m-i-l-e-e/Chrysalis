#include "PatternImporter.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTemporaryFile>

#include "CLOAPIInterface.h"

#include "PatternsContainer.h"

#include "Logging.h"
#define LOGGER_NAME "Pattern Importer"

using namespace Chrysalis;

PatternImporter::PatternImporter(Project* project): project_(project) {}

PatternImporter::~PatternImporter() {
    delete project_;
}

void PatternImporter::import() const {
    LOG_INFO("Importing pattern from project: {}", project_->getName());
    project_->getInstructions()->execute();

    QJsonObject root;
    QJsonArray patternList;
    for (const auto& pattern: *project_->getPatterns()) {
        for (const auto patternSpace = pattern->getSpace();
             const auto& outline: *patternSpace->getOutline()) {
            QJsonObject patternObject;
            patternObject["Name"] = QString("%1 - %2")
                                    .arg(pattern->getName().data())
                                    .arg(outline->getName().data());
            QJsonArray lineList;
            QJsonObject prevPointObject;
            for (const auto& pointName: outline->getPoints()) {
                const auto point = patternSpace->getPoint(pointName);
                QJsonObject pointObject;
                pointObject["ID"] = QString::number(reinterpret_cast<std::size_t>(point));
                QJsonObject position;
                position["x"] = point->x();
                position["y"] = point->y();
                pointObject["Position"] = position;

                if (!prevPointObject.empty()) {
                    QJsonArray pointList;
                    pointList.push_back(prevPointObject);
                    pointList.push_back(pointObject);
                    QJsonObject lineObject;
                    lineObject["PointList"] = pointList;
                    lineList.push_back(lineObject);
                }

                prevPointObject = pointObject;
            }
            QJsonObject shapeInfo;
            shapeInfo["LineList"] = lineList;
            patternObject["ShapeInfo"] = shapeInfo;
            patternList.push_back(patternObject);
        }
        std::cout << std::endl;
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
