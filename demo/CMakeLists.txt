cmake_minimum_required(VERSION 3.15)
project(TengineDemo VERSION 0.0.0 LANGUAGES CXX)

option(BUILD_TENGINE_TEST_APPLICATION "Build internal tengine test application" ON)

if(BUILD_TENGINE_TEST_APPLICATION)
    add_executable(tenginedemo main.cpp)
    target_link_libraries(tenginedemo PRIVATE tengine)
endif()