# StarletLogger

A lightweight logging utility for C++ applications.

## Using as a Dependency

```cmake
include(FetchContent)

FetchContent_Declare(StarletLogger GIT_REPOSITORY https://github.com/Masonlet/StarletLogger.git GIT_TAG main)
FetchContent_MakeAvailable(StarletLogger)

target_link_libraries(YourAppName PRIVATE StarletLogger)
```
