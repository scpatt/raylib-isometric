cmake_minimum_required(VERSION 3.31)
project(raylib_demo)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

FetchContent_MakeAvailable(raylib)

add_executable(raylib_demo
    main.cpp
    src/utils/iso.h
    src/utils/iso.cpp
    src/constants.h
    src/utils/texture_manager.h
    src/core/entity.cpp
    src/core/entity.h
)

target_link_libraries(raylib_demo PRIVATE raylib)