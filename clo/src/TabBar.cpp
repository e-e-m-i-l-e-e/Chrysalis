#include "clo-ui-common/TabBar.h"

using namespace CloUICommon;

TabBar::TabBar(QWidget *parent): QTabBar(parent) {
    this->setExpanding(true);
    this->setDocumentMode(true);
}
