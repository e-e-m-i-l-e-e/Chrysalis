#include "BaseDialogContainerPlugin.h"

#include "BaseDialogContainer.h"

QWidget* BaseDialogContainerPlugin::createWidget(QWidget* parent) {
    return new UI::BaseDialogContainer(parent);
}

QStringList BaseDialogContainerPlugin::domXmlContent() const {
    return {
        containerXml("content", "QVBoxLayout"),
        containerXml("footer", "QHBoxLayout")
    };
}
