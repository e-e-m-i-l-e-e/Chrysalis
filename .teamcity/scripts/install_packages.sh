#!/usr/bin/env bash
set -ex

curl -LO https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 23

sudo add-apt-repository -y ppa:bkryza/clang-uml

sudo apt update
sudo apt install -y cmake build-essential pkg-config graphviz gcovr clang-23 clang-tidy-23 clang-uml