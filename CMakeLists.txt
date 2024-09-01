cmake_minimum_required(VERSION 3.28)
project(c_databases
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(config.h.in config.h)
include_directories(${CMAKE_BINARY_DIR})
file(TO_CMAKE_PATH "${CMAKE_SOURCE_DIR}/cmake" MY_CMAKE_SCRIPTS_DIR)
set(CMAKE_MODULE_PATH "${MY_CMAKE_SCRIPTS_DIR}" ${CMAKE_MODULE_PATH})

include(fetch_content_wrapper)
init_fetch_content_wrapper()

include(CTest)

add_subdirectory(src)
add_subdirectory(test)
