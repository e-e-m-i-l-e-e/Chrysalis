#include "PatternImporter.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

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
    QJsonObject root;
    QJsonArray patternList;
    std::cout << "Pattern size: " << project_->getPatterns()->count() << std::endl;
    for (const auto& pattern: *project_->getPatterns()) {
        const auto patternObject = QJsonObject();
        patternObject["Name"] = "Test";
        std::cout << "Points size: " << pattern->getSpace()->getPoints().size();
        for (const auto& [name, point]: pattern->getSpace()->getPoints()) {
            std::cout << name << ": " << point << std::endl;
        }
    }

    root["PatternList"] = patternList;

    QJsonDocument doc(root);

    const auto filePath = "C:\\Life\\Design\\Apps\\Chrysalis\\.misc\\pattern.json";
    // QFile file(filePath);
    // if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    //     qWarning() << "Cannot open file:" << filePath;
    //     return;
    // }
    //
    // file.write(doc.toJson(QJsonDocument::Indented));
    // file.close();

    if (!PATTERN_API->ImportPatternJSON(filePath)) {
        LOG_ERROR("Failed to import pattern: {}", filePath);
    }
}
