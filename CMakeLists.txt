cmake_minimum_required(VERSION 3.12)
project(CPU)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPU CPU.cpp CPU.h Compiler.cpp Compiler.h main.cpp
        makebuffstr.cpp makebuffstr.h print_log.cpp print_log.h stack.cpp stack.h enum_cmd.h commands.h)