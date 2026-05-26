# Cursed creation of a tired mind, this should keep the all-powerful CMake gods happy enough

cmake_minimum_required(VERSION 3.15)
project(TarnishedEngine VERSION 0.0.0 LANGUAGES CXX)
include(FetchContent)


# Global config
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})

option(BUILD_TENGINE_TESTS "Build all tengine unit tests" ON)
option(BUILD_TENGINE_RUNTIME "Build tengine runtime executable" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)


# Engine metadata
set(TENGINE_ARCH "${CMAKE_SYSTEM_PROCESSOR}")
set(TENGINE_BUILD_TYPE "${CMAKE_BUILD_TYPE}")
set(TENGINE_PLATFORM "${CMAKE_SYSTEM}")
string(TIMESTAMP TENGINE_BUILD_TIME "%Y-%m-%d %H:%M")
set(TENGINE_BUILD_NOTES "Build notes not specified." CACHE STRING "Custom notes for this build of TarnishedEngine.")

set(TENGINE_LICENSE [[TarnishedEngine (c) 2026 DIY Labs
TarnishedEngine is licensed under the MIT license
]])
set(THIRDPARTY_LICENSES [[TarnishedEngine uses the following third-party software. For more details, pass the -l or --license flags
cxxopts (https://github.com/jarro2783/cxxopts) by Jarryd Beck, licensed under the MIT license
fmtlib (https://github.com/fmtlib/fmt) by Victor Zverovich and {fmt} contributors, licensed under the MIT license
termcolor (https://github.com/ikalnytskyi/termcolor) by Ihor Kalnytskyi, all rights reserved
]])

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tengine/tengine_build_details.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/tengine/tengine_build_details.hpp
)


# Dependencies
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 12.1.0)
FetchContent_MakeAvailable(fmt)

# libtengine
set(TENGINE_SOURCES
        src/tengine/util/logger/logger.cpp
        src/tengine/util/logger/sinks/terminal_sink.cpp
        src/tengine/util/logger/sinks/file_sink.cpp
        src/tengine/util/cfgparse/parser.cpp
        src/tengine/util/cfgparse/serializer.cpp
        src/tengine/console/console.cpp
)
set(TENGINE_HEADERS
        include/tengine/util/logger/filter.hpp
        include/tengine/util/logger/i_logsink.hpp
        include/tengine/util/logger/logger.hpp
        include/tengine/util/logger/logger_macros.hpp
        include/tengine/util/logger/log_level.hpp
        include/tengine/util/logger/sinks/file_sink.hpp
        include/tengine/util/logger/sinks/terminal_sink.hpp
        include/tengine/util/cfgparse/cfg_node.hpp
        include/tengine/util/cfgparse/parser.hpp
        include/tengine/util/cfgparse/serializer.hpp
        include/tengine/console/convar.hpp
        include/tengine/console/i_conoutput.hpp
        include/tengine/console/console.hpp
        include/tengine/console/i_console.hpp
        include/tengine/util/filesystem/recur_file_by_ext.hpp
)

add_library(tengine STATIC ${TENGINE_SOURCES} ${TENGINE_HEADERS})
target_link_libraries(tengine PUBLIC fmt::fmt)

target_include_directories(tengine
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include>
)

target_compile_features(tengine PUBLIC cxx_std_17)


# tengine tests
if(BUILD_TENGINE_TESTS)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/heads/main.zip)
    set(gtest_forced_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

    foreach(test_source ${TEST_SOURCES})
        get_filename_component(test_name ${test_source} NAME_WE)
        add_executable(${test_name} ${test_source})
        target_link_libraries(${test_name} PRIVATE tengine gtest_main)

        add_custom_command(TARGET ${test_name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tests/testdata $<TARGET_FILE_DIR:${test_name}>/testdata)

        include(GoogleTest)
        gtest_discover_tests(${test_name} WORKING_DIRECTORY $<TARGET_FILE_DIR:${test_name}>)
        message(STATUS "Registered GTest test ${test_name}")
    endforeach()

endif()