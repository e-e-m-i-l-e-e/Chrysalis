#ifndef CLOEXTENSIONS_ACCORDIONTITLECONTAINERPLUGIN_H
#define CLOEXTENSIONS_ACCORDIONTITLECONTAINERPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class AccordionTitleContainerPlugin: public QObject, public QDesignerCustomWidgetInterface {

    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QString name() const override;

    QString group() const override;

    QString toolTip() const override;

    QString whatsThis() const override;

    QString includeFile() const override;

    QIcon icon() const override;

    bool isContainer() const override;

    QWidget * createWidget(QWidget *parent) override;

    QString domXml() const override;
};


#endif //CLOEXTENSIONS_ACCORDIONTITLECONTAINERPLUGIN_H