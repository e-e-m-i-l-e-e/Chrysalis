#include "TableContentContainerExtension.h"

#include <utility>

TableContentContainerExtension::TableContentContainerExtension(UI::TableContentContainer *widget, QObject *parent, QVector<int> indexes)
: ContainerExtension(widget, parent, std::move(indexes)) {}
