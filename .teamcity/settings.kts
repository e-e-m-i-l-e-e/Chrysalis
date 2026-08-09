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
        param("artifactory.user", "admin")
        password("artifactory.api.key", "credentialsJSON:2811189a-9381-40ae-b4f7-e33e32bd5784")

        password("filebrowser.api.key", "credentialsJSON:a25a4bd9-18c8-4ed8-87ce-4c12970ffb25")

        checkbox("skip.tests", "true", label = "Skip Tests", checked = "true", unchecked = "false")
        checkbox("skip.diagrams", "true", label = "Skip Diagrams Generation", checked = "true", unchecked = "false")
    }

    vcs {
        root(DslContext.settingsRoot)
    }

    steps {
        script {
            name = "Install Required Packages"
            id = "Install_Required_Packages"
            scriptContent = """
                set -ex

                sudo add-apt-repository ppa:bkryza/clang-uml
                sudo apt update
                sudo apt install -y cmake build-essential pkg-config clang-uml
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

                conan install . --build=missing --output-folder=.conan -o app=Chrysalis -s build_type=Debug
                conan upload "*" --confirm -r chrysalis-conan
            """.trimIndent()
        }
        script {
            name = "CMake Build"
            id = "CMake_Build"
            scriptContent = """
                set -ex
                cmake --build --preset conan-debug
            """.trimIndent()
        }
        script {
            name = "Generate Documentation"
            id = "Generate_Documentation"
            scriptContent = """
                set -ex
                [ "%skip.diagrams%" = "false" ] && cmake --build --preset conan-debug --target GenerateUML
                cmake --build --preset conan-debug --target GenerateDoxygen
                cmake --build --preset conan-debug --target Documentation
            """.trimIndent()
        }
        script {
            name = "Upload Documentation"
            id = "Upload_Documentation"
            scriptContent = """
                set -ex
                tar -czf documentation.tar.gz .conan/build/Debug/docs
                curl -X POST \
                  -H "Authorization: Bearer %filebrowser.api.key%" \
                  --data-binary @documentation.tar.gz \
                  "https://filebrowser.lab.eemilee.me/api/resources?path=%2Ftemp%2Fdocumentation.tar.gz&source=RootFS&override=true"

                curl -X POST \
                  -H "Authorization: Bearer %filebrowser.api.key%" \
                  -H "Content-Type: application/json" \
                  "https://filebrowser.lab.eemilee.me/api/resources/unarchive" \
                  -d '{
                    "fromSource": "RootFS",
                    "path": "/temp/documentation.tar.gz",
                    "destination": "/static/chrysalis/docs",
                    "deleteAfter": true
                  }'
            """.trimIndent()
        }
        script {
            name = "Run Tests"
            id = "Run_Tests"
            scriptContent = """
                set -ex
                ctest --preset conan-debug --output-on-failure
            """.trimIndent()

            conditions {
                equals("skip.tests", "false")
            }
        }
    }

    features {
        perfmon {}
    }
})