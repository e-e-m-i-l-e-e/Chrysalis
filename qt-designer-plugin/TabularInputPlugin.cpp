#include <TabularInput.h>
#include <TabularInputPlugin.h>

TabularInputPlugin::TabularInputPlugin(QObject *parent) : QObject(parent) {}

QString TabularInputPlugin::name() const        { return "TabularInput"; }
QString TabularInputPlugin::group() const       { return "My Custom Widgets"; }
QString TabularInputPlugin::toolTip() const     { return "A reusable widget"; }
QString TabularInputPlugin::whatsThis() const   { return ""; }
QString TabularInputPlugin::includeFile() const { return "TabularInput.h"; }
QIcon   TabularInputPlugin::icon() const        { return QIcon(); }
bool    TabularInputPlugin::isContainer() const { return true; }

QWidget *TabularInputPlugin::createWidget(QWidget *parent) {
    return new TabularInput(parent);
}

bool TabularInputPlugin::isInitialized() const { return m_initialized; }

void TabularInputPlugin::initialize(QDesignerFormEditorInterface *) {
    if (m_initialized) return;
    m_initialized = true;
}