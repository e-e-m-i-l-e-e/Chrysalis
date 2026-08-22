#!/usr/bin/env bash
set -ex

APP="${1:?Application name is required}"
BUILD_TYPE="${2:?Build type is required}"

. "$PYTHON_VENV"/bin/activate

CodeChecker analyze .build/"$BUILD_TYPE"/compile_commands.json --analyzers clang-tidy clangsa --ctu                    \
                                                                                                                       \
            --analyzer-config                                                                                          \
                                                                                                                       \
                clangsa:mode=deep                                                                                      \
                clangsa:unroll-loops=true                                                                              \
                clangsa:inline-lambdas=true                                                                            \
                clangsa:c++-inlining=methods                                                                           \
                clangsa:report-in-main-source-file=true                                                                \
                clang-tidy:take-config-from-directory=true                                                             \
                                                                                                                       \
            --enable prefix:core                                                                                       \
            --enable prefix:unix                                                                                       \
            --enable prefix:deadcode                                                                                   \
            --enable prefix:security                                                                                   \
            --enable prefix:cplusplus                                                                                  \
                                                                                                                       \
            --enable optin.core                                                                                        \
            --enable optin.taint                                                                                       \
            --enable optin.cplusplus                                                                                   \
            --enable optin.performance                                                                                 \
                                                                                                                       \
            --enable alpha.unix                                                                                        \
            --enable alpha.core                                                                                        \
            --enable alpha.clone                                                                                       \
            --enable alpha.security                                                                                    \
            --enable alpha.cplusplus                                                                                   \
            --disable alpha.cplusplus.IteratorRange                                                                    \
                                                                                                                       \
            --output .build/"$BUILD_TYPE"/"$APP"/codechecker -c                                                        \
            --skip .docs/CodeChecker-"$APP".skip -j 4 --timeout 600

CodeChecker store .build/"$BUILD_TYPE"/"$APP"/codechecker                                                              \
            --url https://codechecker.lab.eemilee.me/Chrysalis                                                         \
            --name "$APP"                                                                                              \
            --force --trim-path-prefix "$(pwd)/"