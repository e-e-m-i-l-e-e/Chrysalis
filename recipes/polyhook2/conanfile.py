from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.scm import Git

class PolyHook2Conan(ConanFile):
    name = "polyhook2"
    version = "2.0"
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {
        "shared": True,
        "fPIC": True
    }

    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    def source(self):
        git = Git(self)
        git.clone(
            url="https://github.com/stevemk14ebr/PolyHook_2_0.git",
            target=".",
            args=["--depth=1", "--recurse-submodules", "--shallow-submodules"],
            hide_url=False
        )

    def build(self):
        cmake = CMake(self)
        cmake.configure(variables={
            "POLYHOOK_BUILD_SHARED_LIB": "ON" if self.options.shared else "OFF",
            "POLYHOOK_BUILD_STATIC_RUNTIME": self.settings.compiler.runtime != "dynamic"
        })
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["PolyHook_2"]