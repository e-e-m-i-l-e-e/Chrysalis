#!/usr/bin/env bash
set -ex

BUILD_TYPE="${1:?Build type is required}"
SKIP_DIAGRAMS="${2:?SKIP_DIAGRAMS is required}"

dot -Tsvg .build/"$BUILD_TYPE"/graph/dependencies.dot -o .build/"$BUILD_TYPE"/dependencies.svg

if [[ "$SKIP_DIAGRAMS" == "false" ]]; then
    cmake --build .build/"$BUILD_TYPE" --target GenerateUML
fi

cmake --build .build/"$BUILD_TYPE" --target GenerateDoxygen
cmake --build .build/"$BUILD_TYPE" --target GenerateCoverageReport
cmake --build .build/"$BUILD_TYPE" --target GenerateDocumentation