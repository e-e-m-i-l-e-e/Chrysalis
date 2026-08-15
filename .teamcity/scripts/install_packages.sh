#!/usr/bin/env bash
set -ex

sudo add-apt-repository -y ppa:bkryza/clang-uml

sudo apt update
sudo apt install -y cmake build-essential pkg-config graphviz clang-19 clang-uml clang-tidy-19 gcovr