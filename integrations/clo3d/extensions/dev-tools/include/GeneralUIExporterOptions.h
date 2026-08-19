#ifndef CHRYSALIS_GENERALUIEXPORTEROPTIONS_H
#define CHRYSALIS_GENERALUIEXPORTEROPTIONS_H

#include "BaseNativeShortcutHandler.h"
#include "BaseUIExporterOptions.h"

namespace CLO3D {
    class GeneralUIExporterOptions: public BaseUIExporterOptions {
        struct Keys {
            inline static const QString SHORTCUT = "shortcut";
            inline static const QString PICK_BY_MOUSE = "pickMyMouse";
        };
        struct Defaults {
            inline static const QKeySequence SHORTCUT = QKeySequence("Ctrl+Shift+E");
            static constexpr bool PICK_BY_MOUSE = false;
        };
    public:
        void read(const QSettings* settings) override;
        void write(QSettings* settings) override;

        [[nodiscard]] QKeySequence getShortcut() const;
        [[nodiscard]] bool getPickMyMouse() const;

        void setShortcut(const QKeySequence& shortcut);
        void setPickMyMouse(bool pickByMouse);
        void setShortcutHandler(BaseNativeShortcutHandler* shortcutHandler);
    private:
        QKeySequence shortcut_ = Defaults::SHORTCUT;
        bool pickByMouse_ = Defaults::PICK_BY_MOUSE;

        BaseNativeShortcutHandler* shortcutHandler_ = nullptr;
    };
}

#endif //CHRYSALIS_GENERALUIEXPORTEROPTIONS_H