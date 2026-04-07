#include "AccordionTitleContainerExtension.h"

#include <utility>

#include "Logger.h"

AccordionTitleContainerExtension::AccordionTitleContainerExtension(UI::AccordionTitleContainer* container, QObject* parent, QVector<int> indexes)
    : ContainerExtension(container, parent, std::move(indexes)) {}
