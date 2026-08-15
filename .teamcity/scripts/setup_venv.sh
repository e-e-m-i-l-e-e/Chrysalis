#!/usr/bin/env bash
set -ex

python3 -m venv "$PYTHON_VENV"
source "$PYTHON_VENV"/bin/activate
python -m pip install --upgrade pip
pip install -r requirements.txt