package _Self
import jetbrains.buildServer.configs.kotlin.BuildType
import jetbrains.buildServer.configs.kotlin.buildFeatures.perfmon
import jetbrains.buildServer.configs.kotlin.buildSteps.script

object Build : BuildType({
    name = "Build"

    params {
        password("env.FILEBROWSER_API_KEY", "credentialsJSON:11fe4b58-4972-4bd2-9b84-f87664304acc")
        password("env.CC_ANALYZER_BIN", "clang-tidy:/usr/bin/clang-tidy-19;clangsa:/usr/bin/clang-19")

        checkbox("skip.tests", "false", label = "Skip Tests", checked = "true", unchecked = "false")
        checkbox("skip.diagrams", "true", label = "Skip Diagrams Generation", checked = "true", unchecked = "false")
        checkbox("skip.analysis", "true", label = "Skip Static Code Analysis", checked = "true", unchecked = "false")
    }

    vcs {
        root(HttpsGithubComEEMILEEChrysalisRefsHeadsDevelop)
    }

    steps {
        script {
            name = "[Debug] Chrysalis: CMake Build"
            id = "Chrysalis_CMake_Build_Debug"
            scriptContent = ".teamcity/scripts/build.sh Chrysalis Debug"
        }
        script {
            conditions {
                equals("skip.tests", "false")
            }
            name = "[Debug] Chrysalis: Run Tests"
            id = "Chrysalis_Run_Tests_Debug"
            scriptContent = ".teamcity/scripts/test.sh Debug"
        }
        script {
            name = "Generate Documentation"
            id = "Generate_Documentation"
            scriptContent = ".teamcity/scripts/generate_docs.sh Debug %skip.diagrams%"
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