#!/usr/bin/env bash
set -ex

APP="${1:?Application name is required}"
BUILD_TYPE="${2:?Build type is required}"
SKIP_DIAGRAMS="${3:?SKIP_DIAGRAMS is required}"
SANITIZER="${4:?Sanitizer is required}"

dot -Tsvg .build/"$BUILD_TYPE"/graph/dependencies.dot -o "$OUTPUT_DIR"/docs/diagrams/"$APP"-dependencies.svg

if [[ "$SKIP_DIAGRAMS" == "false" ]]; then
    cmake --build .build/"$BUILD_TYPE" --target GenerateUML
fi

cmake --build .build/"$BUILD_TYPE" --target GenerateDoxygen
if [[ "$SANITIZER" != "TSan" ]]; then
    cmake --build .build/"$BUILD_TYPE" --target GenerateCoverageReport
fi
cmake --build .build/"$BUILD_TYPE" --target GenerateDocumentation