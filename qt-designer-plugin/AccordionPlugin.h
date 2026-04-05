#ifndef CLOEXTENSIONS_ACCORDIONPLUGIN_H
#define CLOEXTENSIONS_ACCORDIONPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class AccordionPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")

public:
    AccordionPlugin() = default;

    QString name() const override;

    QString group() const override;

    QString toolTip() const override;

    QString whatsThis() const override;

    QString includeFile() const override;

    QIcon icon() const override;

    bool isContainer() const override;

    QWidget * createWidget(QWidget *parent) override;

    bool isInitialized() const override;

    void initialize(QDesignerFormEditorInterface *core) override;

    QString domXml() const override;

    QString codeTemplate() const override;

private:
    bool m_initialized = false;
};

#endif //CLOEXTENSIONS_ACCORDIONPLUGIN_H