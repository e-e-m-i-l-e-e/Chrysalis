import jetbrains.buildServer.configs.kotlin.*

import _Self.HttpsGithubComEEMILEEChrysalisRefsHeadsDevelop
import _Self.InstallAndPushDependencies
import _Self.Build

version = "2026.1"

project {
    vcsRoot(HttpsGithubComEEMILEEChrysalisRefsHeadsDevelop)

    buildType(Build)
    buildType(InstallAndPushDependencies)

    buildTypesOrder = arrayListOf(
        InstallAndPushDependencies,
        Build
    )

    params {
        param("env.PYTHON_VENV", "%teamcity.agent.home.dir%/Chrysalis/venv")

        param("env.ARTIFACTORY_USER", "admin")
        password("env.ARTIFACTORY_API_KEY", "credentialsJSON:2811189a-9381-40ae-b4f7-e33e32bd5784")
    }
}