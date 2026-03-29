cmake_minimum_required(VERSION 3.15)
project(TarnishedEngine VERSION 0.0.0 LANGUAGES CXX)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(TENGINE_ARCH "${CMAKE_SYSTEM_PROCESSOR}")
set(TENGINE_BUILD_TYPE "${CMAKE_BUILD_TYPE}")
set(TENGINE_PLATFORM "${CMAKE_SYSTEM}")

option(BUILD_TENGINE_TESTS "Build all tengine unit tests" on)

string(TIMESTAMP TENGINE_BUILD_TIME "%Y-%m-%d %H:%M")

set(TENGINE_BUILD_NOTES "Build notes not specified." CACHE STRING "Custom notes for this build of TarnishedEngine.")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tengine/tengine_build_details.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/tengine/tengine_build_details.hpp
)

set(TENGINE_SOURCES
        src/tengine/temp.cpp
        include/tengine/util/logger/ILogSink.hpp
        include/tengine/util/logger/LogLevel.hpp
        include/tengine/util/logger/Logger.cpp
        include/tengine/util/logger/Logger.hpp
        include/tengine/util/logger/Logger.hpp
        include/tengine/util/logger/sinks/FileSink.hpp
        src/tengine/util/logger/sinks/FileSink.cpp
        # tengine cpp files
)

add_library(tengine ${TENGINE_SOURCES})

target_include_directories(tengine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)

option(BUILD_TENGINE_TEST_APPLICATION "Build internal tengine test application" ON)

if(BUILD_TENGINE_TEST_APPLICATION)

    add_executable(TengineTestApp demo/main.cpp)
    target_link_libraries(TengineTestApp PRIVATE tengine)

endif()

FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/heads/main.zip)
set(gtest_forced_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} PRIVATE tengine gtest_main)
    include(GoogleTest)
    gtest_discover_tests(${test_name})
    message(STATUS "Registered GTest test ${test_name}")
endforeach()

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/tests/testdata" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")