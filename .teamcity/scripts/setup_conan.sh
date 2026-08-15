set -ex

. "$PYTHON_VENV"/bin/activate

conan remote add chrysalis-conan https://artifactory.lab.eemilee.me/artifactory/api/conan/chrysalis-conan --force
conan remote login chrysalis-conan "$ARTIFACTORY_USER" -p "$ARTIFACTORY_API_KEY"
conan remote update --index 0 chrysalis-conan

conan export .recipes/polyhook2
conan export .recipes/clo-sdk

conan download "qt/6.8.3" --only-recipe -r chrysalis-conan
conan download "qt/5.15.16" --only-recipe -r chrysalis-conan

git restore .conan/p