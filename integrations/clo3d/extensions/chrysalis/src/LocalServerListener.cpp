#include "LocalServerListener.h"

#include "PatternImporter.h"

#include "Logging.h"
#define LOGGER_NAME "Chrysalis: Local Server Listener"

using namespace CLO3D;
using namespace Chrysalis;

void LocalServerListener::receive(const QByteArray message) {
    std::unique_ptr<Project> project = Project::fromBytes(message.constData(), message.size());
    const PatternImporter importer(std::move(project));
    importer.import();
}
