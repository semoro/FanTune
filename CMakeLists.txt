cmake_minimum_required(VERSION 3.5)
project(FanTune)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libfantune)

add_subdirectory(fantuned)

add_subdirectory(fantune-gui)

