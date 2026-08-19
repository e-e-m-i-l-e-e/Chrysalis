#ifndef CHRYSALIS_COMMANDSCONTAINER_H
#define CHRYSALIS_COMMANDSCONTAINER_H

#include <QMenu>

#include <CommandDialog.h>

#include "BaseCommandArgumentsWidget.h"

namespace CLO3D {
    class CommandRunner {
    public:
        explicit CommandRunner(QSettings* settings, QMenu* menu);

        template<typename Command, typename Arguments, typename Widget>
            requires std::is_base_of_v<BaseCommand, Command> &&
            std::is_base_of_v<BaseCommandArguments, Arguments> &&
            std::is_base_of_v<UI::BaseCommandArgumentsWidget, Widget>
        void add() {
            const auto& action = menu_->addAction(Arguments::NAME);
            QObject::connect(action, &QAction::triggered, [this] {
                const auto arguments = new Arguments(settings_);
                const auto dialog = new UI::CommandDialog(Arguments::NAME, new Widget(arguments), new Command(arguments));
                dialog->exec();
            });
        }
    private:
        QMenu* menu_;
        QSettings* settings_;
    };
}

#endif //CHRYSALIS_COMMANDSCONTAINER_H