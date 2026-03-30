#ifndef CLOEXTENSIONS_EXTENSIONSSETTINGS_H
#define CLOEXTENSIONS_EXTENSIONSSETTINGS_H

#include <Windows.h>

#include <QLineEdit>
#include <QSettings>

#include "MVDialog.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class ExtensionsSettings;
}

QT_END_NAMESPACE

class ExtensionsSettings : public MVDialog {
    Q_OBJECT
public:

    explicit ExtensionsSettings(QWidget *parent = nullptr);
    ~ExtensionsSettings() override;

    void exportUI() const;

private slots:
    void saveSettings();
    void resetSettings();

protected:
    void showEvent(QShowEvent *) override;

private:
    void loadSettings();

    void exportJson() const;
    void exportXML() const;

    struct Key {

        const static inline QString UI_EXPORTER = "UIExporter";

        const static inline QString GENERAL = "General";

        const static inline QString ROOT_FOLDER = "rootFolder";
        const static inline QString FILE_NAME = "fileName";
        const static inline QString CLASS_NAME = "className";
        const static inline QString OBJECT_NAME = "objectName";
        const static inline QString ENABLED = "enabled";
        const static inline QString PICK_WIDGET_BY_MOUSE_POSITION = "pickWidgetByMouse";

        const static inline QString SHORTCUT = "shortcut";
        const static inline QString SHORTCUT_MODIFIERS = "modifiers";
        const static inline QString SHORTCUT_KEY = "key";

        struct Json {
            const static inline QString JSON = "Json";
            const static inline QString VISIBLE_ONLY = "visibleOnly";
            const static inline QString IGNORE_CSS = "ignoreCSS";
        };

        struct XML {
            const static inline QString Xml = "XML";
            const static inline QString EXPORT_ICONS = "exportIcons";
            const static inline QString UI_COMPATIBLE = "uiCompatible";
        };

        // Defaults ----------------------------------------------------------------------------------------------------
        const static inline QString DEFAULT_ROOT_FOLDER = QString(CLO_HOME).append("/.extensions");
        const static inline QString DEFAULT_FILE_NAME = "ui";

        static constexpr UINT DEFAULT_MODIFIERS = 6;
        static constexpr UINT DEFAULT_KEY = 'E'; // Ctrl + Shift
        // -------------------------------------------------------------------------------------------------------------
    };

    struct Shortcut : QObject {
        explicit Shortcut(ExtensionsSettings *parent);
        ~Shortcut() override;

        bool registerShortcut(QLineEdit* shortcutLineEdit) const;
        bool eventFilter(QObject *watched, QEvent *event) override;

        static LRESULT CALLBACK trigger(int nCode, WPARAM wParam, LPARAM lParam);

        UINT modifiers = Key::DEFAULT_MODIFIERS;
        UINT key = Key::DEFAULT_KEY;
        HHOOK messageHook = nullptr;
    };

    Ui::ExtensionsSettings *ui;
    QSettings settings;
    Shortcut shortcut;
};


#endif //CLOEXTENSIONS_EXTENSIONSSETTINGS_H