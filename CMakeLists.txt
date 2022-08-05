cmake_minimum_required(VERSION 3.2)

project(avrSim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O0 -g -Wpedantic -Wextra")
set (SOURCES
    src/main.cpp
    src/fetcher.cpp
    src/processor.cpp
    src/decoder.cpp
)

add_executable(
    avrSim
    ${SOURCES}
)
target_include_directories(avrSim PUBLIC inc)
