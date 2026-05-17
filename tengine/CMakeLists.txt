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

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tengine/tengine_build_details.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/tengine/tengine_build_details.hpp
)


# Dependencies
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 12.1.0)
FetchContent_MakeAvailable(fmt)

# libtengine
set(TENGINE_SOURCES
        src/tengine/util/logger/Logger.cpp
        src/tengine/util/logger/sinks/TerminalSink.cpp
        src/tengine/util/logger/sinks/FileSink.cpp
        src/tengine/util/cfgparse/Parser.cpp
        src/tengine/util/cfgparse/Serializer.cpp
        src/tengine/console/Console.cpp
)
set(TENGINE_HEADERS
        include/tengine/util/logger/Filter.hpp
        include/tengine/util/logger/ILogSink.hpp
        include/tengine/util/logger/Logger.hpp
        include/tengine/util/logger/LoggerMacros.hpp
        include/tengine/util/logger/LogLevel.hpp
        include/tengine/util/logger/sinks/FileSink.hpp
        include/tengine/util/logger/sinks/TerminalSink.hpp
        include/tengine/util/cfgparse/CFGNode.hpp
        include/tengine/util/cfgparse/Parser.hpp
        include/tengine/util/cfgparse/Serializer.hpp
        include/tengine/console/ConVar.hpp
        include/tengine/console/IConOutput.hpp
        include/tengine/console/Console.hpp
        include/tengine/console/IConsole.hpp
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


# tengine runtime
set(TENGINE_RUNTIME_HEADERS
    include/tengine/runtime/CmdOpts.hpp
)

set(TENGINE_RUNTIME_SOURCES
    src/tengine/runtime/main.cpp
)

if(BUILD_TENGINE_RUNTIME)
    add_executable(tengine_runtime ${TENGINE_RUNTIME_HEADERS} ${TENGINE_RUNTIME_SOURCES})
    target_link_libraries(tengine_runtime PRIVATE tengine)

endif()


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

        include(GoogleTest)
        gtest_discover_tests(${test_name})
        message(STATUS "Registered GTest test ${test_name}")
    endforeach()
endif()


# Runtime assets
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/tests/testdata" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/tengine-internal-assets" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")