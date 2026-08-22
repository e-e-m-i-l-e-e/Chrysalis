#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "XmlUIExporter.h"
#include "ExtensionsManager.h"
#include "BaseUIExporterTest.h"
#include "XmlUIExporterOptions.h"
#include "data/TestWidget_AllTypes.h"

#include <QStackedWidget>

using namespace CLO3D;

namespace {
    class XmlUIExporterTest: public BaseUIExporterTest {
    protected:
        [[nodiscard]] QString testDirectory() const override {
            return "xml";
        }
    };
    TEST_P(XmlUIExporterTest, Export) {
        auto options = std::make_unique<XmlUIExporterOptions>();
        options->read(settings());
        XmlUIExporter exporter(std::move(options));
        exporter.exportUI(GetParam().widgets());
        ExtensionsManager::executor_->wait(XmlUIExporter::EXPORT_TASK_NAME);
    }
    INSTANTIATE_TEST_SUITE_P(Export, XmlUIExporterTest, testing::ValuesIn(BaseUIExporterTest::testData));
}
