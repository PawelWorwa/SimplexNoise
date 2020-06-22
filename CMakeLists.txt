cmake_minimum_required(VERSION 3.9)
project(SimplexNoise)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(SimplexNoise
        README.md
        LICENSE
        examples/RandomWorld.cpp
        SimplexNoise.cpp
        SimplexNoise.hpp)

set(SFML_DIR ${SFML_PATH})
find_package(SFML 2.5 COMPONENTS graphics audio)

target_link_libraries(SimplexNoise sfml-graphics sfml-audio)