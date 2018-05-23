cmake_minimum_required(VERSION 2.8)
project(udf_json)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
ADD_DEFINITIONS(-O3 -Wall -g -DHAVE_DLOPEN -DNDEBUG)

if(APPLE)
    ADD_DEFINITIONS(-std=c++0x)
endif()
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

