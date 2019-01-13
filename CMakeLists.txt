cmake_minimum_required(VERSION 3.13)
project(SimplexNoise)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(SimplexNoise
        LICENSE
        main.cpp
        README.md
        SimplexNoise.cpp
        SimplexNoise.hpp)

set(SFML_DIR ${SFML_PATH})
find_package(SFML 2.5 COMPONENTS graphics audio)

target_link_libraries(SimplexNoise sfml-graphics sfml-audio)