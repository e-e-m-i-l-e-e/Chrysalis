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
    project_->getInstructions()->execute();
    LOG_INFO("Importing pattern from project: {}", project_->getName());
    QJsonObject root;
    QJsonArray patternList;
    std::cout << "Pattern size: " << project_->getPatterns()->count() << std::endl;
    for (const auto& pattern: *project_->getPatterns()) {
        const auto patternObject = QJsonObject();
        const auto patternSpace = pattern->getSpace();
        for (const auto& outline: *patternSpace->getOutline()) {
            patternObject["Name"] = QString("%1 - %2").arg(pattern->getName().data()).arg(outline->getName().data());
            for (const auto& pointName: outline->getPoints()) {
                std::cout << "Point: " << pointName.data() << std::endl;
            }
        }
        std::cout << std::endl;
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
