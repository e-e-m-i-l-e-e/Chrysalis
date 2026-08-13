#include <gtest/gtest.h>

#include "XmlUIExporter.h"
#include "BaseUIExporterTest.h"

class XmlUIExporterTest: public BaseUIExporterTest {};
TEST_P(XmlUIExporterTest, Export) {
    auto options = std::make_unique<XmlUIExporterOptions>();
    options->read(settings());
    XmlUIExporter exporter(std::move(options));
    exporter.exportUI(GetParam().widgets());
}
INSTANTIATE_TEST_SUITE_P(Export, XmlUIExporterTest, testing::ValuesIn(BaseUIExporterTest::testData));
