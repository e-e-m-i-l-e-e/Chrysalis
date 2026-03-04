from conan import ConanFile
from conan.tools.cmake import cmake_layout

class CLOExtensionsConan(ConanFile):
    name = "CLOExtensions"
    version = "1.0.0"

    settings = "os", "arch", "compiler", "build_type"

    requires = [
        "qt/5.15.16",
        "polyhook2/2.0"
    ]

    generators = "CMakeConfigDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    default_options = {
        "qt/5.15.16:shared": True,

        "qt/5.15.16:openssl": False,
        "qt/5.15.16:with_mysql": False
    }