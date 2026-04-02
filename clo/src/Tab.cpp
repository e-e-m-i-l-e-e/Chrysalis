#include "clo-ui-common/Tab.h"
#include "clo-ui-common/TabBar.h"

using namespace CloUICommon;

Tab::Tab(QWidget *parent): QTabWidget(parent) {
    this->setTabBar(new TabBar(this));
}
