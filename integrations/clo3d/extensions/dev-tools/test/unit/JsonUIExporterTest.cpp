#include <gtest/gtest.h>

#include "JsonUIExporter.h"
#include "BaseUIExporterTest.h"

class JsonUIExporterTest: public BaseUIExporterTest {};
TEST_P(JsonUIExporterTest, Export) {
    auto options = std::make_unique<JsonUIExporterOptions>();
    options->read(settings());
    JsonUIExporter exporter(std::move(options));
    exporter.exportUI(GetParam().widgets());
}
INSTANTIATE_TEST_SUITE_P(Export, JsonUIExporterTest, testing::ValuesIn(BaseUIExporterTest::testData));