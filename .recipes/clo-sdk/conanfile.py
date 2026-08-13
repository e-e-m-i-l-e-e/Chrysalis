from conan import ConanFile
from conan.tools.files import get, copy, collect_libs
import os


class CloSdkConan(ConanFile):
    name = "clo-sdk"
    version = "9.1.0"
    package_type = "shared-library"
    description = "CLO3D official API/SDK for building C++ plugins (Windows, v2025.2.236)"
    url = "https://developer.clo3d.com"

    settings = "os", "arch"

    def source(self):
        get(self, "https://s3.us-east-1.amazonaws.com/Outside_Work/CLO_API/9_1_0/CLO_SDK_v2025.2.236_WIN.zip")

    def build(self):
        pass

    def package(self):
        api_root = os.path.join(self.source_folder, "CLO_SDK_v2025.2.236_WIN/CLOAPIInterface")

        copy(self, "CLOAPIInterface.h",
             src=api_root,
             dst=os.path.join(self.package_folder, "include"))

        copy(self, "*.h",
             src=os.path.join(api_root, "include"),
             dst=os.path.join(self.package_folder, "include", "include"))

        copy(self, "*.lib",
             src=os.path.join(api_root, "Lib"),
             dst=os.path.join(self.package_folder, "lib"))

        copy(self, "*.dll",
             src=os.path.join(api_root, "Lib"),
             dst=os.path.join(self.package_folder, "bin"))

    def package_info(self):
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.libdirs = ["lib"]
        self.cpp_info.bindirs = ["bin"]
        self.cpp_info.libs = collect_libs(self)
