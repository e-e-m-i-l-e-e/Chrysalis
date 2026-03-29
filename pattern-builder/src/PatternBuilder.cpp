#include "PatternBuilder.h"

#include "clo-ui-common/IconButton.h"

void PatternBuilder::configureStatusBar(QWidget *parent) {
    const auto patternBuilderIcon = new CloUICommon::IconButton(parent);
    // patternBuilderIcon->setGeometry(parent->width() * 2 / 3, 2, 500, 20);
    patternBuilderIcon->show();
}
