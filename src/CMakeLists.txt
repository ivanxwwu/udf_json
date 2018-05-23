cmake_minimum_required(VERSION 2.8)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps/rapidjson/include
        ${PROJECT_SOURCE_DIR}/deps/mysql/include)
ADD_LIBRARY(udf_json SHARED udf_json.cpp)