> ⚠️ This is a personal project in progress.

## Tech stack

C++23 · CGAL · OpenGL / GLSL · Qt / QML · Boost · CMake · Conan · PolyHook2 · GoogleTest

# Chrysalis

App which provides a way to build fashion design patterns in a form of **algorithm (script)** and can be integrated with other industry standard tools and apps (currently it's just CLO3D).
Does similar work as parametric CAD systems, however provides some fashion design specific functions and features to describe dependencies between pattern's points, edges, darts etc. 

## Build targets

**Chrysalis Lab (`lab/`) is the main application** — a standalone Qt QML app where user can create, visualize and export patterns.

**CLO3D Integration** (`integrations/clo3d`) — produces dynamic library and CLO3D launcher which injects this library on startup. Uses PolyHook2, official CLO3D API and Qt metadata system to extend app with new features.

### Other modules

| Module | Purpose                                                                                                                                                                                                                                                                              |
|---|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `pattern` | Main module. Represents patterns as parametric instructions (`pattern/include/instructions`) evaluated through the constant or calculated arguments (`pattern/include/arguments`). Fires events when user input is changed or current rendered pattern is stale (used by `renderer`) |
| `pattern/composer` | Module which is used for testing and temporary it's providing macros and operator overloading to substitute scripting capabilities.                                                                                                                                                  |
| `renderer` | OpenGL/GLSL renderer of current pattern                                                                                                                                                                                                                                              |
| `integrations/hooks/` | Library wrapped around PolyHook2. Currently it's functional header only library, but will be refactored into static library in future.                                |
| `logging/` | Shared logging used across all modules.                                                                                                                                                                                                                                              |

Class diagrams are located in [`.docs/diagrams`](.docs/diagrams).

## Building

See build instructions below.

### 1. Create a Python virtual environment
**Windows**
```
python -m venv .python/venv
.python\venv\Scripts\activate
```
**Linux (WSL)**
```
python3 -m venv .python/venv-wsl
source .python/venv-wsl/bin/activate
```

### 2. Install requirements and custom Conan recipes
```
python -m pip install --upgrade pip
pip install -r requirements.txt
conan export .recipes/polyhook2
conan export .recipes/clo-sdk
conan download "qt/5.15.16" -r conancenter --only-recipe
conan download "qt/6.8.3" -r conancenter --only-recipe
git restore .conan/p
```

### 3. Build dependencies
**Windows**
```
mklink /J C:\Chrysalis "%CD%"
cd C:\Chrysalis
conan install . --build=missing --output-folder=.conan -o app=Chrysalis -s build_type=Debug
conan install . --build=missing --output-folder=.conan -o app=CLO3D -s build_type=RelWithDebInfo
```
**Linux**
```
conan install . --build=missing --output-folder=.conan -o app=Chrysalis -s build_type=Debug -pr:h wsl -pr:b wsl
conan install . --build=missing --output-folder=.conan -o app=CLO3D -s build_type=RelWithDebInfo -pr:h wsl -pr:b wsl
```