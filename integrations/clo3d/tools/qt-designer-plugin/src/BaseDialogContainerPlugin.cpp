#include "BaseDialogContainerPlugin.h"

#include "BaseDialogContainer.h"

using namespace CLO3D::UI;

QWidget* BaseDialogContainerPlugin::createWidget(QWidget* parent) {
    return new BaseDialogContainer(parent);
}

QStringList BaseDialogContainerPlugin::domXmlContent() const {
    return {
        containerXml("content", "QVBoxLayout"),
        containerXml("footer", "QHBoxLayout")
    };
}
