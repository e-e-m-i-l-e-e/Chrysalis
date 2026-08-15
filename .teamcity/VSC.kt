package _Self
import jetbrains.buildServer.configs.kotlin.vcs.GitVcsRoot

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