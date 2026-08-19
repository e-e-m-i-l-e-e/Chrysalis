#include "BaseUIExporterTest.h"

#include <memory>

#include "BaseUIExporterOptions.h"
#include "Logging.h"

using namespace CLO3D;

void BaseUIExporterTest::SetUp() {
    const auto exporterDirectory = QString(CLO3D_TEST_TEMP_DIR) + "/" + testDirectory();
    QDir dir(exporterDirectory);
    dir.removeRecursively();
    if (!dir.mkpath(dir.absolutePath())) {
        throw std::runtime_error("Failed to create directory for test data: " + dir.absolutePath().toStdString());
    }
    if (settingsFile_.open()) {
        settings_ = std::make_unique<QSettings>(settingsFile_.fileName());
        settings_->setValue(
            BaseUIExporterOptions::Keys::ROOT_FOLDER, exporterDirectory
        );
    }
}

QSettings* BaseUIExporterTest::settings() const {
    return settings_.get();
}

std::vector<UIExporterData> BaseUIExporterTest::testData = {
    UIExporterData([] -> std::forward_list<QWidget*> {
        return {
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
            new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(), new QWidget(),
        };
    })
};