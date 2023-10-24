# pth_2023
Workshop demo repo.<br/><br/>

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.<br/><br/>

## Build dependencies
These are the dependencies for the compilation of all the targets
```
cmake
cmake-format
clang-format
doxygen
gcov
ccache
```

After installing these clone the necessary submodules by running:
```
sh tools/init-submodules.sh
```
<br/>

# Build instructions for development
## Create make files for each target (via cmake)
Run the cmake command and output the make recipe in the build folder
```
mkdir -p build/debug
cd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
```
<br/>

## Build the continuous integration targets
Supported targets for continuous integration include:

    - Documentation
    - Coverage
    - Automatic tests
    - Static code analysis
    - Dynamic code analysis
<br/>

Run the jobs by running
```
make Documentation
make Coverage
make all && make test
```
<br/>

## Run code linters locally 
In order to merge to master the code in the pull request should be formatted using the checks defined in the project.
```
clang-format -i $filename
cmake-format -i $filename
```
<br/>

Code formating compliance can also be checked via pre commit hook.
```
cd <project-path>
cp tools/pre-commit.sh .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
```
<br/><br/>

## Code analysis
```
mkdir -p build/debug++
cd build/debug++
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_DIAGNOSTIC_TOOLS=ON ../..
make all
```
<br/><br/>

## Build and execute project

1. Create project target in release mode
```
mkdir -p build/release
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release ../..
```
Note : For windows build.
 - Install build toolchain with [MinGW](http://www.mingw.org/wiki/getting_started)
 - Set the cmake option for windows build DUNIX_COMPILATION=OFF
```
cmake -DCMAKE_BUILD_TYPE=Release -DUNIX_COMPILATION=OFF ../..
```

2. Build the project
```
make pth_2023
```

3. Execute project target
```
(WINDOWS) double-click executable in bin/pth_2023.exe
(LINUX)   ./bin/pth_2023
```
<br/>

## Future work
- Add contribution guidelines
<br/><br/>

## IDE setup
Visual studio code [config](https://github.com/nolasconapoleao/.vscode)
<br/><br/>

## Generator
Project generated using [cookiecutter project](https://github.com/nolasconapoleao/cookiecutter-template)
