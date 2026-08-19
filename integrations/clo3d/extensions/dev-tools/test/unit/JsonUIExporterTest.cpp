#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "JsonUIExporter.h"
#include "ExtensionsManager.h"
#include "BaseUIExporterTest.h"
#include "JsonUIExporterOptions.h"

#include <QThreadPool>

using namespace CLO3D;

namespace {
    class JsonUIExporterTest: public BaseUIExporterTest {
    protected:
        [[nodiscard]] QString testDirectory() const override {
            return "json";
        }
    };
    TEST_P(JsonUIExporterTest, Export) {
        auto options = std::make_unique<JsonUIExporterOptions>();
        options->read(settings());
        JsonUIExporter exporter(std::move(options));
        exporter.exportUI(GetParam().widgets());
    }
    INSTANTIATE_TEST_SUITE_P(Export, JsonUIExporterTest, testing::ValuesIn(BaseUIExporterTest::testData));
}