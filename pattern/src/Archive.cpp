#include "Archive.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

using namespace Chrysalis;

Project* Archive::read(const char* filePath) {
    try {
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << filePath;
            return nullptr;
        }

        boost::archive::binary_iarchive archive(file);
        Project* project;
        archive >> project;
        return project;
    } catch (const boost::archive::archive_exception &e) {
        std::cout << "Archive error: " << e.what();
    } catch (const std::exception &e) {
        std::cout << "Read error: " << e.what();
    }
    return nullptr;
}

void Archive::write(const char* filePath, Project* project) {
    try {
        std::ofstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << filePath;
            return;
        }

        {
            boost::archive::binary_oarchive archive(file);
            archive << project;
        } // ← archive destructor flushes here before file closes

        file.flush();
        file.close();

        if (file.fail())
            std::cout << "Write failed after close";
        else
            std::cout << "Write successful";

    } catch (const boost::archive::archive_exception &e) {
        std::cout << "Archive error: " << e.what();
    } catch (const std::exception &e) {
        std::cout << "Write error: " << e.what();
    }
}
