#ifndef CLOEXTENSIONS_CONTAINERPLUGIN_H
#define CLOEXTENSIONS_CONTAINERPLUGIN_H

#include "WidgetPlugin.h"

class ContainerPlugin: public WidgetPlugin {
public:
    QString group() const override; // NOLINT(*-use-nodiscard)
    bool isContainer() const override; // NOLINT(*-use-nodiscard)
    void initialize(QDesignerFormEditorInterface *core) override;
    QString domXml() const override; // NOLINT(*-use-nodiscard)
protected:
    [[nodiscard]] virtual QStringList domXmlContent() const = 0;
    static QString containerXml(const QString& objectName, const QString& layoutClassName);
    static QString containerXml(const QString& className, const QString& objectName, const QString& layoutClassName);
private:
    QStringList customContent_;
};


#endif //CLOEXTENSIONS_CONTAINERPLUGIN_H