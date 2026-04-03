//
// Created by emily on 03/04/2026.
//

#ifndef CLOEXTENSIONS_TABULARINPUTPLUGIN_H
#define CLOEXTENSIONS_TABULARINPUTPLUGIN_H
#include <QDesignerCustomWidgetInterface>
#include <QObject>


class TabularInputPlugin: public QObject, public QDesignerCustomWidgetInterface {
public:
    Q_OBJECT
    // This macro is CRITICAL — it registers the plugin interface
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

    explicit TabularInputPlugin(QObject *parent = nullptr);

    // --- Required interface methods ---
    QString name() const override;           // Class name
    QString group() const override;          // Palette group
    QString toolTip() const override;
    QString whatsThis() const override;
    QString includeFile() const override;    // Header to #include in generated code
    QIcon icon() const override;
    bool isContainer() const override;       // true if widget can hold children
    QWidget *createWidget(QWidget *parent) override;
    bool isInitialized() const override;
    void initialize(QDesignerFormEditorInterface *core) override;

// private:
    bool m_initialized = false;
};


#endif //CLOEXTENSIONS_TABULARINPUTPLUGIN_H