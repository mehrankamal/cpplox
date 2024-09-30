cmake_minimum_required(VERSION 3.20)

project(CppLox VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.cc")

add_executable(cclox ${SOURCES})