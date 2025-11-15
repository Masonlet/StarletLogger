# Starlet Logger

![Tests](https://github.com/masonlet/starlet-logger/actions/workflows/test.yml/badge.svg)
[![C++20](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/std/the-standard)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE)

A lightweight logging utility for C++ applications.

## Features
- Four log levels: Info, Debug, Warning, Error
- Automatic stream routing (stdout for info/debug, stderror for warnings/errors)
- Caller, function, and msg context in every log message
- Debug logs compiled out in release builds (NDEBUG)
- Custom warning return value for permissible warnings

<br/>

## Prerequisites
- C++17 or later
- CMake 3.20+

## Using as a Dependency

```cmake
include(FetchContent)

FetchContent_Declare(starlet_logger
  GIT_REPOSITORY https://github.com/masonlet/starlet-logger.git 
  GIT_TAG main
)
FetchContent_MakeAvailable(starlet_logger)

target_link_libraries(app_name PRIVATE starlet_logger)
```

<br/>

## Building and Testing
```bash
# 1. Clone starlet-logger
git clone https://github.com/masonlet/starlet-logger.git
cd starlet-logger

# 2. Create a build directory and generate build files
mkdir build
cd build
cmake -DBUILD_TESTS=ON ..

# 3. Build and run tests
cmake --build .
ctest
```

<br/>

## License
MIT License - see [LICENSE](./LICENSE) for details.
