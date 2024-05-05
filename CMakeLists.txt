cmake_minimum_required(VERSION 3.28)
project(SISTOPE_LAB1_1_2024 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(SISTOPE_LAB1_1_2024
        LAB/funciones.c
        LAB/funciones.h
        LAB/main.c)
