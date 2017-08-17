cmake_minimum_required(VERSION 3.7)
project(SIMULATION)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        simulationdisplay.cpp)

add_executable(RUN simulationrun.cpp)            # Add executable target with source files listed in SOURCE_FILES variable
add_executable(DISPLAY simulationdisplay.cpp)
