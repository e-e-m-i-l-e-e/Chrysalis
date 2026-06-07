# Build
## 1. Create python virtual environment
### Windows
```
python -m venv .python/venv
.python\venv\Scripts\activate
```
### Linux (WSL)
```
python3 -m venv .python/venv-wsl
source .python/venv-wsl/bin/activate
```
## 2. Install requirements and custom conan recipes
```
python -m pip install --upgrade pip
pip install -r requirements.txt
conan export .recipes/polyhook2
conan export .recipes/clo-sdk
conan download "qt/5.15.16" -r conancenter --only-recipe
conan download "qt/6.8.3" -r conancenter --only-recipe
git restore .conan/p
```
## 3. Build dependencies
### Windows
```
mklink /J C:\Chrysalis "%CD%"
cd C:\Chrysalis
conan install . --build=missing --output-folder=.conan -o app=Chrysalis -s build_type=Debug
conan install . --build=missing --output-folder=.conan -o app=CLO3D -s build_type=RelWithDebInfo
```
### Linux
```
conan install . --build=missing --output-folder=.conan -o app=Chrysalis -s build_type=Debug -pr:h wsl -pr:b wsl
conan install . --build=missing --output-folder=.conan -o app=CLO3D -s build_type=RelWithDebInfo -pr:h wsl -pr:b wsl
```