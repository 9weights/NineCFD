cmake_minimum_required(VERSION 3.10)
project(NineCFD)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(NineCFD 
        main.cpp
        solver.cpp
        solver.h)
