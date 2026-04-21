from conan import ConanFile
from conan.tools.cmake import cmake_layout

class FashionDesignAppsConan(ConanFile):
    name = "FashionDesignApps"
    version = "1.0.0"

    settings = "os", "arch", "compiler", "build_type"

    requires = [
        # Common
        "spdlog/1.17.0",
        "gtest/1.17.0",
        
        # CLO3D
        "qt/5.15.16",
        "clo-sdk/9.1.0",
        "polyhook2/2.0"
    ]
    options = {
        "app": [None, "clo3d", "mobile"]
    }
    default_options = {
        "qt/5.15.16:shared": True,

        "qt/5.15.16:qttools": True,

        "qt/5.15.16:opengl": None,
        "qt/5.15.16:openssl": False,
        "qt/5.15.16:with_pq": False,
        "qt/5.15.16:with_odbc": False,
        "qt/5.15.16:with_zstd": False,
        "qt/5.15.16:with_pcre2": False,
        "qt/5.15.16:with_mysql": False,
        "qt/5.15.16:with_libjpeg": False,
        "qt/5.15.16:with_sqlite3": False,
        "qt/5.15.16:with_freetype": False
    }
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        if self.options.app == "clo3d":

        if self.settings.build_type != "RelWithDebInfo":
            self.requires("qt/6.10.1")

    def layout(self):
        cmake_layout(self)