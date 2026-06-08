#include "BaseCommand.h"

BaseCommand::BaseCommand(BaseCommandArguments* arguments): arguments_(arguments) {}

BaseCommand::~BaseCommand() {
    delete arguments_;
}
