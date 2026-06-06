## Build
```
Windows:
mklink /J C:\Chrysalis "C:\Life\Design\Apps\Chrysalis"
python -m venv .venv
.venv\Scripts\activate
pip install --upgrade pip
pip install -r requirements.txt
conan export .recipes/polyhook2
conan export .recipes/clo-sdk
conan download "qt/5.15.16" -r conancenter --only-recipe
conan download "qt/6.8.3" -r conancenter --only-recipe
git restore .conan/p
cd C:\Chrysalis
conan install . --build=missing --output-folder=.conan -o app=CLO3D -s build_type=RelWithDebInfo
conan install . --build=missing --output-folder=.conan -o app=Chrysalis -s build_type=Debug
cmake -B .build -S . -G Ninja -DCMAKE_TOOLCHAIN_FILE=.conan/build/Release/generators/conan_toolchain.cmake
cmake --build .build

Linux:
python3 -m venv .venv
source .venv/bin/activate
pip install --upgrade pip
pip install -r requirements.txt
conan export .recipes/polyhook2
conan export .recipes/clo-sdk
conan download "qt/5.15.16" -r conancenter --only-recipe
conan download "qt/6.8.3" -r conancenter --only-recipe
git restore .conan/p
conan install . --build=missing --output-folder=.conan -o app=CLO3D -s build_type=RelWithDebInfo -pr:h wsl -pr:b wsl
conan install . --build=missing --output-folder=.conan -o app=Chrysalis -s build_type=Debug -pr:h wsl -pr:b wsl
```