cmake_minimum_required(VERSION 3.15)
project(TarnishedRuntime VERSION 0.0.0 LANGUAGES CXX)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})


# Runtime metadata
set(RUNTIME_ARCH "${CMAKE_SYSTEM_PROCESSOR}")
set(RUNTIME_BUILD_TYPE "${CMAKE_BUILD_TYPE}")
set(RUNTIME_PLATFORM "${CMAKE_SYSTEM}")
string(TIMESTAMP RUNTIME_BUILD_TIME "%Y-%m-%d %H:%M")
set(RUNTIME_BUILD_NOTES "Build notes not specified." CACHE STRING "Custom notes for this build of Tarnished Runtime.")

set(RUNTIME_LICENSE [[Tarnished Runtime (c) 2026 DIY Labs
Tarnished Runtime is licensed under the MIT license
]])
set(THIRDPARTY_LICENSES [[Tarnished Runtime uses the following third-party software. For more details, pass the -l or --license flags
cxxopts (https://github.com/jarro2783/cxxopts) by Jarryd Beck, licensed under the MIT license
fmtlib (https://github.com/fmtlib/fmt) by Victor Zverovich and {fmt} contributors, licensed under the MIT license
termcolor (https://github.com/ikalnytskyi/termcolor) by Ihor Kalnytskyi, all rights reserved
]])


# Dependencies
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/include/runtime/runtime_build_details.hpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/generated/runtime/runtime_build_details.hpp
)

FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 12.1.0)
FetchContent_MakeAvailable(fmt)


# Runtime files
set(RUNTIME_HEADERS
        include/runtime/cmd_opts.hpp
        include/runtime/core/init.hpp
        include/runtime/core/RuntimeGlobals.hpp
)

set(RUNTIME_SOURCES
        src/runtime/main.cpp
        src/runtime/core/init.cpp
)

add_executable(tengine_runtime ${RUNTIME_HEADERS} ${RUNTIME_SOURCES})
target_link_libraries(tengine_runtime PRIVATE tengine)

target_include_directories(tengine_runtime PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/generated
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/tengine-runtime-assets" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")