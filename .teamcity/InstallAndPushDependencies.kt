package _Self
import jetbrains.buildServer.configs.kotlin.BuildType
import jetbrains.buildServer.configs.kotlin.buildFeatures.perfmon
import jetbrains.buildServer.configs.kotlin.buildSteps.script

object InstallAndPushDependencies : BuildType({
    name = "Install And Push Dependencies"

    params {
        checkbox("chrysalis.debug", "true", label = "Chrysalis (Debug)", checked = "true", unchecked = "false")
        checkbox("chrysalis.release", "false", label = "Chrysalis (Release)", checked = "true", unchecked = "false")
        checkbox("clo3d.debug", "true", label = "CLO3D (Debug)", checked = "true", unchecked = "false")
        checkbox("clo3d.release", "false", label = "CLO3D (Release)", checked = "true", unchecked = "false")
    }

    vcs {
        root(HttpsGithubComEEMILEEChrysalisRefsHeadsDevelop)
    }

    steps {
        script {
            name = "Install Packages"
            id = "Install_Packages"
            scriptContent = ".teamcity/scripts/install_packages.sh"
        }
        script {
            name = "Setup Python Virtual Environment"
            id = "Setup_Python_Virtual_Environment"
            scriptContent = ".teamcity/scripts/setup_venv.sh"
        }
        script {
            name = "Setup Conan"
            id = "Setup_Conan"
            scriptContent = ".teamcity/scripts/setup_conan.sh"
        }
        script {
            conditions {
                equals("chrysalis.debug", "true")
            }
            name = "[Debug] Chrysalis: Conan Install And Push Dependencies"
            id = "Chrysalis_Conan_Install_And_Push_Dependencies_Debug"
            scriptContent = ".teamcity/scripts/conan_install.sh Chrysalis Debug"
        }
        script {
            conditions {
                equals("chrysalis.release", "true")
            }
            name = "[Release] Chrysalis: Conan Install And Push Dependencies"
            id = "Chrysalis_Conan_Install_And_Push_Dependencies_Release"
            scriptContent = ".teamcity/scripts/conan_install.sh Chrysalis Release"
        }
        script {
            conditions {
                equals("clo3d.debug", "true")
            }
            name = "[Debug] CLO3D: Conan Install And Push Dependencies"
            id = "CLO3D_Conan_Install_And_Push_Dependencies_Debug"
            scriptContent = ".teamcity/scripts/conan_install.sh CLO3D Debug"
        }
        script {
            conditions {
                equals("clo3d.release", "true")
            }
            name = "[Release] CLO3D: Conan Install And Push Dependencies"
            id = "CLO3D_Conan_Install_And_Push_Dependencies_Release"
            scriptContent = ".teamcity/scripts/conan_install.sh CLO3D Release"
        }
    }

    features {
        perfmon {
        }
    }
})

