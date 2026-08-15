#!/usr/bin/env bash
set -ex

BUILD_TYPE="${1:?Build type is required}"

. "$PYTHON_VENV"/bin/activate

CodeChecker analyze .build/"$BUILD_TYPE"/compile_commands.json --analyzers clang-tidy --output .build/"$BUILD_TYPE"/codechecker -j 4
set +e
CodeChecker parse .build/"$BUILD_TYPE"/codechecker --export html --output .build/"$BUILD_TYPE"/docs/codechecker
STATUS=$?
set -e

if [ "$STATUS" -ne 0 ] && [ "$STATUS" -ne 2 ]; then
    exit "$STATUS"
fi