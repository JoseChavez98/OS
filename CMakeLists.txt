cmake_minimum_required(VERSION 3.13)
project(OS)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(OS magos.c)
