package _Self
import jetbrains.buildServer.configs.kotlin.BuildType
import jetbrains.buildServer.configs.kotlin.buildFeatures.perfmon
import jetbrains.buildServer.configs.kotlin.buildSteps.script

object Build : BuildType({
    name = "Build"

    params {
        password("env.FILEBROWSER_API_KEY", "credentialsJSON:11fe4b58-4972-4bd2-9b84-f87664304acc")

        select("build.type", "Debug", label = "Build Type", options = listOf("Debug", "Release"))
        select("build.sanitizer", "ASan", label = "Sanitizer", options = listOf("ASan", "TSan"))
        select("app.name", "All", label = "App Name", options = listOf("Chrysalis", "CLO3D", "All"))

        checkbox("skip.tests", "false", label = "Skip Tests", checked = "true", unchecked = "false")
        checkbox("skip.diagrams", "true", label = "Skip Diagrams Generation", checked = "true", unchecked = "false")
        checkbox("skip.analysis", "true", label = "Skip Static Code Analysis", checked = "true", unchecked = "false")

        param("env.OUTPUT_DIR", ".build/%build.type%/BuildArtifacts")
        param("env.CC_ANALYZER_BIN", "clang-tidy:/usr/bin/clang-tidy-23;clangsa:/usr/bin/clang-23")
    }

    vcs {
        root(HttpsGithubComEEMILEEChrysalisRefsHeadsDevelop)
    }

    steps {
        script {
            conditions {
                matches("app.name", "^(Chrysalis|All)$")
            }
            name = "Chrysalis: CMake Build"
            id = "Chrysalis_CMake_Build"
            scriptContent = ".teamcity/scripts/build.sh Chrysalis %build.type% %build.sanitizer%"
        }
        script {
            conditions {
                equals("skip.tests", "false")
                matches("app.name", "^(Chrysalis|All)$")
            }
            name = "Chrysalis: Run Tests"
            id = "Chrysalis_Run_Tests"
            scriptContent = ".teamcity/scripts/test.sh %build.type%"
        }
        script {
            conditions {
                matches("app.name", "^(Chrysalis|All)$")
            }
            name = "Chrysalis: Generate Documentation"
            id = "Chrysalis_Generate_Documentation"
            scriptContent = ".teamcity/scripts/generate_docs.sh Chrysalis %build.type% %skip.diagrams% %build.sanitizer%"
        }
        script {
            conditions {
                equals("skip.analysis", "false")
                matches("app.name", "^(Chrysalis|All)$")
            }
            name = "Chrysalis: Perform code analysis"
            id = "Chrysalis_Perform_Code_Analysis"
            scriptContent = ".teamcity/scripts/analyze_code.sh Chrysalis %build.type%"
        }
        script {
            conditions {
                matches("app.name", "^(CLO3D|All)$")
            }
            name = "CLO3D: CMake Build"
            id = "CLO3D_CMake_Build"
            scriptContent = ".teamcity/scripts/build.sh CLO3D %build.type% %build.sanitizer%"
        }
        script {
            conditions {
                equals("skip.tests", "false")
                matches("app.name", "^(CLO3D|All)$")
            }
            name = "CLO3D: Run Tests"
            id = "CLO3D_Run_Tests"
            scriptContent = ".teamcity/scripts/test.sh %build.type%"
        }
        script {
            conditions {
                matches("app.name", "^(CLO3D|All)$")
            }
            name = "CLO3D: Generate Documentation"
            id = "CLO3D_Generate_Documentation"
            scriptContent = ".teamcity/scripts/generate_docs.sh CLO3D %build.type% %skip.diagrams% %build.sanitizer%"
        }
        script {
            conditions {
                equals("skip.analysis", "false")
                matches("app.name", "^(CLO3D|All)$")
            }
            name = "CLO3D: Perform code analysis"
            id = "CLO3D_Perform_Code_Analysis"
            scriptContent = ".teamcity/scripts/analyze_code.sh CLO3D %build.type%"
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