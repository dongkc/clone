cmake_minimum_required(VERSION 2.8)
project (Clone)

SET(CMAKE_CXX_FLAGS "-std=c++0x -pthread")

include_directories (${CMAKE_SOURCE_DIR}/src/lib)


file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory (src)


