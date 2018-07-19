cmake_minimum_required(VERSION 3.10)

project(FringeTree CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(googletest EXCLUDE_FROM_ALL)
add_subdirectory(fringetree)
add_subdirectory(main)
