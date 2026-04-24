#ifndef CLOEXTENSIONS_WIDGETPLUGIN_H
#define CLOEXTENSIONS_WIDGETPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class WidgetPlugin: public QObject, public QDesignerCustomWidgetInterface {
public:
    QString name() const override; // NOLINT(*-use-nodiscard)
    QString group() const override; // NOLINT(*-use-nodiscard)
    QString toolTip() const override; // NOLINT(*-use-nodiscard)
    QString whatsThis() const override; // NOLINT(*-use-nodiscard)
    QString includeFile() const override; // NOLINT(*-use-nodiscard)
    QIcon icon() const override; // NOLINT(*-use-nodiscard)
    bool isContainer() const override;
    void initialize(QDesignerFormEditorInterface *core) override;
};

#endif //CLOEXTENSIONS_WIDGETPLUGIN_H