from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.cmake import CMakeToolchain, CMakeDeps

class FashionDesignAppsConan(ConanFile):
    name = "FashionDesignApps"
    version = "1.0.0"

    settings = "os", "arch", "compiler", "build_type"

    # Common
    requires = [
        "spdlog/1.17.0",
        "gtest/1.17.0",
        "cgal/6.1.1",
        "glad/2.0.8",
        "glm/1.0.1"
    ]
    options = {
        "app": ["none", "CLO3D", "Chrysalis"]
    }
    default_options = {
        "app": "none"
    }

    def requirements(self):
        if self.settings.os == "Linux":
            return

        if self.options.app == "CLO3D":
            self.requires("qt/5.15.16")
            self.requires("clo-sdk/9.1.0")
            self.requires("polyhook2/2.0")
        elif self.options.app == "Chrysalis":
            self.requires("qt/6.8.3")

    def configure(self):
        self.options["boost"].without_test = True
        if self.settings.os == "Linux":
            return

        if self.options.app == "CLO3D":
            self.options["qt/5.15.16"].shared = True
            self.options["qt/5.15.16"].qttools = True
            self.options["qt/5.15.16"].openssl = False
            self.options["qt/5.15.16"].with_pq = False
            self.options["qt/5.15.16"].with_odbc = False
            self.options["qt/5.15.16"].with_zstd = False
            self.options["qt/5.15.16"].with_pcre2 = False
            self.options["qt/5.15.16"].with_mysql = False
            self.options["qt/5.15.16"].with_libjpeg = False
            self.options["qt/5.15.16"].with_sqlite3 = False
            self.options["qt/5.15.16"].with_freetype = False

        elif self.options.app == "Chrysalis":
            self.options["qt/6.8.3"].shared = True
            self.options["qt/6.8.3"].openssl = False
            self.options["qt/6.8.3"].with_pq = False
            self.options["qt/6.8.3"].with_md4c = False
            self.options["qt/6.8.3"].with_odbc = False
            self.options["qt/6.8.3"].with_brotli = False
            self.options["qt/6.8.3"].with_sqlite3 = False
            self.options["qt/6.8.3"].qtdeclarative = True
            self.options["qt/6.8.3"].qtshadertools = True
            self.options["qt/6.8.3"].with_harfbuzz = False

    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.variables["APP"] = str(self.options.app)
        toolchain.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def layout(self):
        cmake_layout(self)