from conan import ConanFile
from conan.tools.cmake import cmake_layout

class FashionDesignAppsConan(ConanFile):
    name = "FashionDesignApps"
    version = "1.0.0"

    settings = "os", "arch", "compiler", "build_type"

    requires = [
        "spdlog/1.17.0",
        "gtest/1.17.0"
    ]
    default_options = {
        "qt/5.15.16:qttools": True
    }
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        if self.settings.build_type != "Debug":
            self.requires("qt/5.15.16")
            self.requires("polyhook2/2.0")
            self.requires("clo-sdk/9.1.0")
        if self.settings.build_type != "RelWithDebInfo":
            self.requires("qt/6.10.1")

    def layout(self):
        cmake_layout(self)