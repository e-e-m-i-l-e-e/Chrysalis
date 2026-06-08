#ifndef CHRYSALIS_EXPORTPATTERNCOMMANDARGUMENTS_H
#define CHRYSALIS_EXPORTPATTERNCOMMANDARGUMENTS_H

#include "BaseCommandArguments.h"
#include "ExtensionsManager.h"

class ExportPatternCommandArguments: public BaseCommandArguments {
    struct Keys {
        static constexpr auto FILE_PATH = "filePath";
    };
    struct Defaults {
        inline static auto FILE_PATH = ExtensionsManager::ROOT_EXTENSIONS_DIR.filePath("pattern.json");
    };
public:
    explicit ExportPatternCommandArguments(QSettings* settings);

    void read() override;
    void write() override;

    const QString& getFilePath() const;
    void setFilePath(const QString& filePath);

    QString getName() override;

    static constexpr auto NAME = "Export Pattern (.json)";
private:
    QString filePath_;
};

#endif //CHRYSALIS_EXPORTPATTERNCOMMANDARGUMENTS_H