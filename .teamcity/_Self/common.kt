package _Self

import jetbrains.buildServer.configs.kotlin.BuildSteps
import jetbrains.buildServer.configs.kotlin.buildSteps.script

fun BuildSteps.installRequiredPackages() {
    script {
        name = "Install Required Packages"
        id = "Install_Required_Packages"
        scriptContent = """
            sudo apt update
            sudo apt install -y cmake build-essential pkg-config
        """.trimIndent()
    }
}

fun BuildSteps.setupPythonVenv() {
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
}

fun BuildSteps.setupConan() {
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
}