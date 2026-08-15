#!/usr/bin/env bash
set -ex

BUILD_TYPE="${1:?Build type is required}"

ctest --test-dir .build/"$BUILD_TYPE" --output-on-failure