cmake_minimum_required(VERSION 3.15)
project(TarnishedEngine VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

option(BUILD_TENGINE_TESTS "Build all tengine unit tests" on)

string(TIMESTAMP TENGINE_BUILD_TIME "%Y-%m-%d %H:%M")

set(TENGINE_BUILD_NOTES "Build notes not specified." CACHE STRING "Custom notes for this build of TarnishedEngine.")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tengine/tengine_version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/tengine/tengine_version.hpp
)

set(TENGINE_SOURCES
    # tengine cpp files
)

add_library(tengine ${TENGINE_SOURCES})

target_include_directories(tengine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)