cmake_minimum_required(VERSION 3.29)
project(2 C)

set(CMAKE_C_STANDARD 23)

add_executable(2 main.c
        structures.h
        functions.h
        functions.c
        mystring.c
        mystring.h
)
