cmake_minimum_required(VERSION 3.16)
project(RubiksCubeSolver VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(rubiks_core
    src/Cube.cpp
    src/Move.cpp
)

target_include_directories(rubiks_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(rubiks_cube_solver src/main.cpp)
target_link_libraries(rubiks_cube_solver PRIVATE rubiks_core)

enable_testing()
add_executable(cube_engine_tests tests/test_cube.cpp)
target_link_libraries(cube_engine_tests PRIVATE rubiks_core)

add_test(NAME cube_engine_tests COMMAND cube_engine_tests)
