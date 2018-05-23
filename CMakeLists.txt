cmake_minimum_required(VERSION 2.8)
project(udf_json)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
ADD_DEFINITIONS(-O3 -Wall -g -DHAVE_DLOPEN -DNDEBUG -std=c++11)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
