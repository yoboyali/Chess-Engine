cmake_minimum_required(VERSION 3.31)
project(Chess_Engine)

set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/raylib")
include_directories(${RAYLIB_DIR}/src)
link_directories(${RAYLIB_DIR}/src)

set(CMAKE_CXX_STANDARD 20)

add_executable(Chess_Engine main.cpp)

target_link_libraries(${PROJECT_NAME}
        raylib
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
)
