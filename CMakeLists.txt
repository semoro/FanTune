cmake_minimum_required(VERSION 3.5)
project(fantune)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(libfantune)

add_subdirectory(fantuned)

add_subdirectory(fantune-gui)

