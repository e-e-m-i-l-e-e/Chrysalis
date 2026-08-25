#ifndef CHRYSALIS_WIDGETPLUGIN_H
#define CHRYSALIS_WIDGETPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

namespace CLO3D::UI {
    class WidgetPlugin: public QObject, public QDesignerCustomWidgetInterface {
    public:
        [[nodiscard]] QString name() const override;
        [[nodiscard]] QString group() const override;
        [[nodiscard]] QString toolTip() const override;
        [[nodiscard]] QString whatsThis() const override;
        [[nodiscard]] QString includeFile() const override;
        [[nodiscard]] QIcon icon() const override;
        [[nodiscard]] bool isContainer() const override;
        void initialize(QDesignerFormEditorInterface *core) override;
    };
}

#endif //CHRYSALIS_WIDGETPLUGIN_H
