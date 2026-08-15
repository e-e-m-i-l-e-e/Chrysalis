set -ex

APP="${1:?Application name is required}"
BUILD_TYPE="${2:?Build type is required}"

. "$PYTHON_VENV"/bin/activate

conan install . --build=missing --output-folder=out -o "&:app=$APP" -s build_type="$BUILD_TYPE" -pr:h linux-host -pr:b linux-build
conan upload "*" --confirm -r chrysalis-conan