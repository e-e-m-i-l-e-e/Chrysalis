#include "BaseUIExporterTest.h"

#include <QApplication>

#include "BaseUIExporterOptions.h"

void BaseUIExporterTest::SetUp() {
    if (settingsFile_.open()) {
        settings_ = std::make_unique<QSettings>(settingsFile_.fileName());
        settings_->setValue(BaseUIExporterOptions::Keys::ROOT_FOLDER, "C:\\Life\\Design\\Apps\\Chrysalis\\.build\\RelWithDebInfo\\BuildArtifacts\\CLO3D\\Test\\temp");
    }
}

QSettings* BaseUIExporterTest::settings() const {
    return settings_.get();
}

std::vector<UIExporterData> BaseUIExporterTest::testData = {
    UIExporterData([] -> std::forward_list<QWidget*> {
        return {new QWidget()};
    })
};