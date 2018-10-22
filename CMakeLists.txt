cmake_minimum_required(VERSION 3.8)
project(paint)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c canvas.c canvas.h draw.c draw.h command.c command.h inputValidation.c inputValidation.h)
add_executable(paint ${SOURCE_FILES})