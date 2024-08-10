cmake_minimum_required(VERSION 3.28)
project(c_databases
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

configure_file(config.h.in config.h)
include_directories(${CMAKE_BINARY_DIR})

include(CTest)

add_subdirectory(src)
add_subdirectory(test)
