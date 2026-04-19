cmake_minimum_required(VERSION 3.21)
project(GDAIMod)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
    geode
    GIT_REPOSITORY https://github.com/geode-sdk/geode.git
    GIT_TAG main
)

FetchContent_MakeAvailable(geode)

add_library(GDAIMod SHARED
    src/main.cpp
)

target_link_libraries(GDAIMod geode)
