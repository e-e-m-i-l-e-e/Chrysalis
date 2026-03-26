from conan import ConanFile
from conan.tools.cmake import cmake_layout

class CLOExtensionsConan(ConanFile):
    name = "CLOExtensions"
    version = "1.0.0"

    settings = "os", "arch", "compiler", "build_type"

    requires = [
        "qt/5.15.16",
        "spdlog/1.17.0",
        "polyhook2/2.0",
        "clo-sdk/9.1.0",

        "gtest/1.17.0"
    ]

    generators = "CMakeConfigDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    default_options = {
        "qt/5.15.16:shared": True,

        "qt/5.15.16:openssl": False,
        "qt/5.15.16:with_mysql": False,

        "qt/5.15.16:qttools": True,

        "polyhook2/2.0:shared": True
    }