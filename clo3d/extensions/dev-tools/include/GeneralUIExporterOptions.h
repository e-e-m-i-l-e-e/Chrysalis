#ifndef FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONS_H
#define FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONS_H

#include <QKeySequence>

#include "BaseUIExporterOptions.h"

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
    void read(const Settings &settings) override;
    void write(const Settings &settings) override;

    [[nodiscard]] QKeySequence getShortcut() const;
    [[nodiscard]] bool getPickMyMouse() const;

    void setShortcut(const QKeySequence& shortcut);
    void setPickMyMouse(bool pickByMouse);
private:
    QKeySequence shortcut_ = Defaults::SHORTCUT;
    bool pickByMouse_ = Defaults::PICK_BY_MOUSE;
};

#endif //FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONS_H