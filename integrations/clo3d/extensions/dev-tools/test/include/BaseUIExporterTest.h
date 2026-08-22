#ifndef CHRYSALIS_BASEUIEXPORTERTEST_H
#define CHRYSALIS_BASEUIEXPORTERTEST_H

#include <gtest/gtest.h>

#include <vector>
#include <memory>

#include <QSettings>
#include <QTemporaryFile>

#include "data/UIExporterData.h"

class BaseUIExporterTest: public ::testing::TestWithParam<UIExporterData> {
public:
    static std::vector<UIExporterData> testData;
protected:
    void SetUp() override;
    void TearDown() override;
    [[nodiscard]] QSettings* settings() const;
    [[nodiscard]] virtual QString testDirectory() const = 0;
private:
    QTemporaryFile settingsFile_;
    std::unique_ptr<QSettings> settings_;
};

#endif //CHRYSALIS_BASEUIEXPORTERTEST_H
