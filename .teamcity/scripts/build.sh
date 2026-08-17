#!/usr/bin/env bash
set -ex

APP="${1:?Application name is required}"
BUILD_TYPE="${2:?Build type is required}"

. "$PYTHON_VENV"/bin/activate

conan install . --output-folder=.conan --lockfile=.conan/lock/"$APP"-"$BUILD_TYPE"-Linux.lock                          \
                -o "&:app=$APP" -s build_type="$BUILD_TYPE" -pr:h linux-host -pr:b linux-build

rm -f .build/"$BUILD_TYPE"/CMakeCache.txt

cmake -S . -B .build/"$BUILD_TYPE" --graphviz=.build/"$BUILD_TYPE"/graph/dependencies.dot                              \
              -DCMAKE_TOOLCHAIN_FILE=.conan/build/"$BUILD_TYPE"/generators/conan_toolchain.cmake                       \
              -DPYTHON_VENV_DIR="$PYTHON_VENV"                                                                         \
              -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

cmake --build .build/"$BUILD_TYPE" -j 6