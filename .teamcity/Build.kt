package _Self
import jetbrains.buildServer.configs.kotlin.BuildType
import jetbrains.buildServer.configs.kotlin.buildFeatures.perfmon
import jetbrains.buildServer.configs.kotlin.buildSteps.script

object Build : BuildType({
    name = "Build"

    params {
        password("env.FILEBROWSER_API_KEY", "credentialsJSON:11fe4b58-4972-4bd2-9b84-f87664304acc")
        password("env.CC_ANALYZER_BIN", "clang-tidy:/usr/bin/clang-tidy-23;clangsa:/usr/bin/clang-23")

        select("build.type", "Debug", label = "Build Type", options = listOf("Debug", "Release"))

        checkbox("skip.tests", "false", label = "Skip Tests", checked = "true", unchecked = "false")
        checkbox("skip.diagrams", "true", label = "Skip Diagrams Generation", checked = "true", unchecked = "false")
        checkbox("skip.analysis", "true", label = "Skip Static Code Analysis", checked = "true", unchecked = "false")
    }

    vcs {
        root(HttpsGithubComEEMILEEChrysalisRefsHeadsDevelop)
    }

    steps {
        script {
            name = "Chrysalis: CMake Build"
            id = "Chrysalis_CMake_Build"
            scriptContent = ".teamcity/scripts/build.sh Chrysalis %build.type%"
        }
        script {
            conditions {
                equals("skip.tests", "false")
            }
            name = "Chrysalis: Run Tests"
            id = "Chrysalis_Run_Tests"
            scriptContent = ".teamcity/scripts/test.sh %build.type%"
        }
        script {
            name = "Chrysalis: Generate Documentation"
            id = "Chrysalis_Generate_Documentation"
            scriptContent = ".teamcity/scripts/generate_docs.sh %build.type% %skip.diagrams%"
        }
        script {
            name = "CLO3D: CMake Build"
            id = "CLO3D_CMake_Build"
            scriptContent = ".teamcity/scripts/build.sh CLO3D %build.type%"
        }
        script {
            conditions {
                equals("skip.tests", "false")
            }
            name = "CLO3D: Run Tests"
            id = "CLO3D_Run_Tests"
            scriptContent = ".teamcity/scripts/test.sh %build.type%"
        }
        script {
            name = "CLO3D: Generate Documentation"
            id = "CLO3D_Generate_Documentation"
            scriptContent = ".teamcity/scripts/generate_docs.sh %build.type% %skip.diagrams%"
        }
        script {
            conditions {
                equals("skip.analysis", "false")
            }
            name = "Perform code analysis"
            id = "Perform_Code_Analysis"
            scriptContent = ".teamcity/scripts/analyze_code.sh Debug"
        }
        script {
            name = "Upload Documentation"
            id = "Upload_Documentation"
            scriptContent = ".teamcity/scripts/upload_docs.sh Debug"
        }
    }

    features {
        perfmon {
        }
    }
})