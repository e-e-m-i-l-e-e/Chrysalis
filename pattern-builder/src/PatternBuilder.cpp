#include "PatternBuilder.h"

#define LOGGER_NAME "Pattern Builder"

#include <CLOAPIInterface.h>
#include <QLayout>

#include "Logger.h"
#include "MVDockingButton.h"
#include "clo-ui-common/IconButton.h"

void PatternBuilder::configureStatusBar(QWidget *parent) {
    const auto patternBuilderIcon = new CloUICommon::IconButton(parent);
    // patternBuilderIcon->setGeometry(parent->width() * 2 / 3, 2, 500, 20);
    patternBuilderIcon->show();
}

void PatternBuilder::configure(QWidget *widget) {
    if (widget->objectName() == "dockingBarContents") {
        LOG_INFO("Configuring right docking bar.");
        const auto patternBuilderDockItem = new MVDockingButton(widget);
        patternBuilderDockItem->setObjectName("mvdockingButton");
        UTILITY_API->UpdateCloStyleForPlugIn(patternBuilderDockItem);
        qobject_cast<QVBoxLayout*>(widget->layout())->insertWidget(0, patternBuilderDockItem);
        patternBuilderDockItem->show();
        widget->update();
    }
}
