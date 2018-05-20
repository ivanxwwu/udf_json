cmake_minimum_required(VERSION 3.7)
project(udf_json)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(udf_json ${SOURCE_FILES})