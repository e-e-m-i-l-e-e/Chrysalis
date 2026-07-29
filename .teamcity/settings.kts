import jetbrains.buildServer.configs.kotlin.*
import jetbrains.buildServer.configs.kotlin.buildFeatures.perfmon
import jetbrains.buildServer.configs.kotlin.buildSteps.script

/*
The settings script is an entry point for defining a TeamCity
project hierarchy. The script should contain a single call to the
project() function with a Project instance or an init function as
an argument.

VcsRoots, BuildTypes, Templates, and subprojects can be
registered inside the project using the vcsRoot(), buildType(),
template(), and subProject() methods respectively.

To debug settings scripts in command-line, run the

    mvnDebug org.jetbrains.teamcity:teamcity-configs-maven-plugin:generate

command and attach your debugger to the port 8000.

To debug in IntelliJ Idea, open the 'Maven Projects' tool window (View
-> Tool Windows -> Maven Projects), find the generate task node
(Plugins -> teamcity-configs -> teamcity-configs:generate), the
'Debug' option is available in the context menu for the task.
*/

version = "2026.1"

project {

    buildType(Pre_Build_Dependencies)
    buildType(Build_2)
}

object Build_2 : BuildType({
    name = "Build"

    vcs {
        root(DslContext.settingsRoot)
    }
})

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
                python3 -m venv .python/venv
                . .python/venv/bin/activate
                python -m pip install --upgrade pip
                pip install -r requirements.txt
            """.trimIndent()
        }
        script {
            name = "Setup Conan"
            id = "Setup_Conan"
            scriptContent = """
                set -e
                . .python/venv/bin/activate
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
            name = "Build And Push Conan Dependencies"
            id = "Build_And_Push_Conan_Dependencies"
            scriptContent = """
                set -e
                . .python/venv/bin/activate
                conan install . --build=missing --output-folder=.conan -o app=Chrysalis -s build_type=Debug -pr:h wsl -pr:b wsl -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
                conan upload "*" -r chrysalis-conan --confirm
            """.trimIndent()
        }
    }

    features {
        perfmon {
        }
    }
})
