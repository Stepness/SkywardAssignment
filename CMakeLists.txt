cmake_minimum_required(VERSION 3.26)
project(Skyward C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Skyward
    grader.c
    grader.h
        control.c)
