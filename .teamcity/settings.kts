import jetbrains.buildServer.configs.kotlin.*
import jetbrains.buildServer.configs.kotlin.buildFeatures.perfmon
import jetbrains.buildServer.configs.kotlin.buildSteps.script
import _Self.*

version = "2026.1"

project {
    buildType(Pre_Build_Dependencies)
    buildType(Build_2)
}

object Pre_Build_Dependencies : BuildType({
    name = "Pre-Build Dependencies"

    params {
        password("artifactory.api.key", "credentialsJSON:2811189a-9381-40ae-b4f7-e33e32bd5784")
        param("artifactory.user", "admin")
    }

    vcs {
        root(DslContext.settingsRoot)
    }

    steps {
        installRequiredPackages()
        setupPythonVenv()
        setupConan()
        script {
            name = "Build And Push Conan Dependencies"
            id = "Build_And_Push_Conan_Dependencies"
            scriptContent = """
                set -e
                . .python/venv/bin/activate
                conan install . --build=missing --output-folder=.conan -o app=Chrysalis -s build_type=Debug -pr:h linux -pr:b linux
                conan upload "*" -r chrysalis-conan --confirm
            """.trimIndent()
        }
    }

    features {
        perfmon {}
    }
})

object Build_2 : BuildType({
    name = "Build"

    params {
        password("artifactory.api.key", "credentialsJSON:2811189a-9381-40ae-b4f7-e33e32bd5784")
        param("artifactory.user", "admin")
    }

    vcs {
        root(DslContext.settingsRoot)
    }

    steps {
        installRequiredPackages()
        setupPythonVenv()
        setupConan()
        script {
            name = "Conan Install"
            id = "Conan_Install"
            scriptContent = """
                set -e
                . .python/venv/bin/activate
                conan install . --output-folder=.conan -o app=Chrysalis -s build_type=Debug -pr:h linux -pr:b linux
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

    dependencies {
        snapshot(Pre_Build_Dependencies) {
            onDependencyFailure = FailureAction.FAIL_TO_START
        }
    }
})