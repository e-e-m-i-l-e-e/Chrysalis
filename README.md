## Build
```
python -m venv .venv
.venv\Scripts\activate
pip install --upgrade pip
pip install -r requirements.txt
conan export recipes/polyhook2
conan export recipes/clo-sdk
conan download "qt/5.15.16" -r conancenter --only-recipe
git restore .conan/p
conan install . --build=missing --output-folder=.conan -o app=CLO3D -s build_type=Release
conan install . --build=missing --output-folder=.conan -o app=mobile -s build_type=Release
cmake -B .build -S . -G Ninja -DCMAKE_TOOLCHAIN_FILE=.conan/build/Release/generators/conan_toolchain.cmake
cmake --build .build
```