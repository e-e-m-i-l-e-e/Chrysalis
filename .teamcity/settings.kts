import jetbrains.buildServer.configs.kotlin.*
import jetbrains.buildServer.configs.kotlin.buildFeatures.perfmon
import jetbrains.buildServer.configs.kotlin.buildSteps.script

version = "2026.1"

project {
    buildType(Build)
}

object Build : BuildType({
    name = "Build"

    params {
        password("artifactory.api.key", "credentialsJSON:2811189a-9381-40ae-b4f7-e33e32bd5784")
        param("artifactory.user", "admin")
    }

    vcs {
        root(DslContext.settingsRoot)
    }

    steps {
        script {
            name = "Install Required Packages"
            id = "Install_Required_Packages"
            scriptContent = """
                sudo apt update
                sudo apt install -y cmake build-essential pkg-config
            """.trimIndent()
        }
        script {
            name = "Setup Python Virtual Environment"
            id = "Setup_Python_Virtual_Environment"
            scriptContent = """
                set -e
                python3 -m venv .python/venv-linux
                . .python/venv-linux/bin/activate
                python -m pip install --upgrade pip
                pip install -r requirements.txt
            """.trimIndent()
        }
        script {
            name = "Setup Conan"
            id = "Setup_Conan"
            scriptContent = """
                set -e
                . .python/venv-linux/bin/activate
                conan remote add chrysalis-conan https://artifactory.lab.eemilee.me/artifactory/api/conan/chrysalis-conan --force
                conan remote login chrysalis-conan %artifactory.user% -p %artifactory.api.key%
                conan export .recipes/polyhook2
                conan export .recipes/clo-sdk
                conan download "qt/5.15.16" -r conancenter --only-recipe
                conan download "qt/6.8.3" -r conancenter --only-recipe
                git restore .conan/p
            """.trimIndent()
        }
        script {
            name = "Conan Install And Push Dependencies"
            id = "Conan_Install_And_Push_Dependencies"
            scriptContent = """
                set -e
                . .python/venv-linux/bin/activate
                conan install . --build=missing --output-folder=.conan -o app=Chrysalis -s build_type=Debug -pr:h linux -pr:b linux -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
                conan upload "*" -r chrysalis-conan --confirm
            """.trimIndent()
        }
        script {
            name = "CMake Build"
            id = "CMake_Build"
            scriptContent = """
                set -e
                cmake --preset conan-debug
                cmake --build --preset conan-debug
            """.trimIndent()
        }
        script {
            name = "Run Tests"
            id = "Run_Tests"
            scriptContent = """
                set -e
                ctest --preset conan-debug --output-on-failure
            """.trimIndent()
        }
    }

    features {
        perfmon {}
    }
})