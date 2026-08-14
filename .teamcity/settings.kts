import jetbrains.buildServer.configs.kotlin.*
import jetbrains.buildServer.configs.kotlin.buildFeatures.perfmon
import jetbrains.buildServer.configs.kotlin.buildSteps.script
import jetbrains.buildServer.configs.kotlin.vcs.GitVcsRoot

version = "2026.1"

project {
    vcsRoot(HttpsGithubComEEMILEEChrysalisRefsHeadsDevelop)

    buildType(Build)
    buildType(InstallAndPushDependencies)

    buildTypesOrder = arrayListOf(
        InstallAndPushDependencies,
        Build
    )
}

object InstallAndPushDependencies : BuildType({
    name = "Install And Push Dependencies"

    params {
        password("artifactory.api.key", "credentialsJSON:2811189a-9381-40ae-b4f7-e33e32bd5784")
        param("artifactory.user", "admin")
    }

    vcs {
        root(HttpsGithubComEEMILEEChrysalisRefsHeadsDevelop)
    }

    steps {
        script {
            name = "Setup Python Virtual Environment"
            id = "Setup_Python_Virtual_Environment"
            scriptContent = """
                set -ex

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
                set -ex

                . .python/venv-linux/bin/activate

                cp .conan/linux-global.conf .conan/global.conf

                conan remote add chrysalis-conan https://artifactory.lab.eemilee.me/artifactory/api/conan/chrysalis-conan --force
                conan remote login chrysalis-conan %artifactory.user% -p %artifactory.api.key%
                conan remote update --index 0 chrysalis-conan

                conan export .recipes/polyhook2
                conan export .recipes/clo-sdk

                conan download "qt/6.8.3" --only-recipe -r chrysalis-conan
                conan download "qt/5.15.16" --only-recipe -r chrysalis-conan

                git restore .conan/p
            """.trimIndent()
        }
        script {
            name = "Chrysalis: Conan Install And Push Dependencies"
            id = "Chrysalis_Conan_Install_And_Push_Dependencies"
            scriptContent = """
                set -ex

                . .python/venv-linux/bin/activate

                conan install . --build=missing --output-folder=.conan -o '&:app=Chrysalis' -s build_type=Debug
                conan upload "*" --confirm -r chrysalis-conan
            """.trimIndent()
        }
        script {
            name = "CLO3D: Conan Install And Push Dependencies"
            id = "CLO3D_Conan_Install_And_Push_Dependencies"
            scriptContent = """
                set -ex

                . .python/venv-linux/bin/activate

                conan install . --build=missing --output-folder=.conan -o '&:app=CLO3D' -s build_type=RelWithDebInfo
                conan upload "*" --confirm -r chrysalis-conan
            """.trimIndent()
        }
    }

    features {
        perfmon {
        }
    }
})

object Build : BuildType({
    name = "Build"

    params {
        password("artifactory.api.key", "credentialsJSON:2811189a-9381-40ae-b4f7-e33e32bd5784")
        password("filebrowser.api.key", "credentialsJSON:11fe4b58-4972-4bd2-9b84-f87664304acc")
        checkbox("skip.tests", "false", label = "Skip Tests", checked = "true", unchecked = "false")
        checkbox("skip.diagrams", "true", label = "Skip Diagrams Generation", checked = "true", unchecked = "false")
        param("artifactory.user", "admin")
    }

    vcs {
        root(HttpsGithubComEEMILEEChrysalisRefsHeadsDevelop)
    }

    steps {
        script {
            name = "Install Required Packages"
            id = "Install_Required_Packages"
            scriptContent = """
                set -ex

                sudo apt update
                sudo add-apt-repository -y ppa:bkryza/clang-uml
                sudo apt install -y cmake build-essential pkg-config clang-uml gcovr
            """.trimIndent()
        }
        script {
            name = "Setup Python Virtual Environment"
            id = "Setup_Python_Virtual_Environment"
            scriptContent = """
                set -ex

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
                set -ex

                . .python/venv-linux/bin/activate

                cp .conan/linux-global.conf .conan/global.conf

                conan remote add chrysalis-conan https://artifactory.lab.eemilee.me/artifactory/api/conan/chrysalis-conan --force
                conan remote login chrysalis-conan %artifactory.user% -p %artifactory.api.key%
                conan remote update --index 0 chrysalis-conan

                conan export .recipes/polyhook2
                conan export .recipes/clo-sdk

                conan download "qt/6.8.3" --only-recipe -r chrysalis-conan
                conan download "qt/5.15.16" --only-recipe -r chrysalis-conan

                git restore .conan/p
            """.trimIndent()
        }
        script {
            name = "Chrysalis: Conan Install And Push Dependencies"
            id = "Chrysalis_Conan_Install_And_Push_Dependencies"
            scriptContent = """
                set -ex

                . .python/venv-linux/bin/activate

                conan install . --build=missing --output-folder=.conan -o '&:app=Chrysalis' -s build_type=Debug
                conan upload "*" --confirm -r chrysalis-conan
            """.trimIndent()
        }
        script {
            name = "CLO3D: Conan Install And Push Dependencies"
            id = "CLO3D_Conan_Install_And_Push_Dependencies"
            scriptContent = """
                set -ex

                . .python/venv-linux/bin/activate

                conan install . --build=missing --output-folder=.conan -o '&:app=CLO3D' -s build_type=RelWithDebInfo
                conan upload "*" --confirm -r chrysalis-conan
            """.trimIndent()
        }
        script {
            name = "CMake Build"
            id = "CMake_Build"
            scriptContent = """
                set -ex

                conan install . --build=missing --output-folder=.conan -o '&:app=Chrysalis' -s build_type=Debug

                cmake --preset conan-debug
                cmake --build --preset conan-debug
            """.trimIndent()
        }
        script {
            name = "Run Tests"
            id = "Run_Tests"

            conditions {
                equals("skip.tests", "false")
            }
            scriptContent = """
                set -ex
                ctest --preset conan-debug --output-on-failure
            """.trimIndent()
        }
        script {
            name = "Generate Documentation"
            id = "Generate_Documentation"
            scriptContent = """
                set -ex
                [ "%skip.diagrams%" = "false" ] && cmake --build --preset conan-debug --target GenerateUML
                cmake --build --preset conan-debug --target GenerateDoxygen
                cmake --build --preset conan-debug --target GenerateCoverageReport
            """.trimIndent()
        }
        script {
            name = "Upload Documentation"
            id = "Upload_Documentation"
            scriptContent = """
                set -ex

                cd .conan/build/Debug
                tar -czvf documentation.tar.gz docs

                curl --fail-with-body -X POST \
                  -H "Authorization: Bearer %filebrowser.api.key%" \
                  --data-binary @documentation.tar.gz \
                  "https://filebrowser.lab.eemilee.me/api/resources?path=%2Ftemp%2Fdocumentation.tar.gz&source=srv&override=true"

                curl --fail-with-body -X POST \
                  -H "Authorization: Bearer %filebrowser.api.key%" \
                  -H "Content-Type: application/json" \
                  -d '{
                    "fromSource": "srv",
                    "path": "/temp/documentation.tar.gz",
                    "destination": "/static/chrysalis",
                    "deleteAfter": true
                  }' \
                  "https://filebrowser.lab.eemilee.me/api/resources/unarchive"
            """.trimIndent()
        }
    }

    features {
        perfmon {
        }
    }
})

object HttpsGithubComEEMILEEChrysalisRefsHeadsDevelop : GitVcsRoot({
    name = "https://github.com/e-e-m-i-l-e-e/Chrysalis#refs/heads/develop"
    url = "https://github.com/e-e-m-i-l-e-e/Chrysalis"
    branch = "refs/heads/develop"
    branchSpec = "refs/heads/*"
    authMethod = password {
        userName = "e-e-m-i-l-e-e"
        password = "credentialsJSON:6cf6309b-1424-43d1-8344-b6bbc29f1bc8"
    }
})