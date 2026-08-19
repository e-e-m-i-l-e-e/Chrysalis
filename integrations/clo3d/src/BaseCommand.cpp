#include "BaseCommand.h"

using namespace CLO3D;

BaseCommand::BaseCommand(BaseCommandArguments* arguments): arguments_(arguments) {}

BaseCommand::~BaseCommand() {
    delete arguments_;
}
