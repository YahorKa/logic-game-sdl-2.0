cmake_minimum_required(VERSION 2.8)
project(Cupboards)

set(CMAKE_CXX_STANDARD 11)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCE_LIB  ${SRC_DIR}/cups.h)
#include_directories(src)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
#add_library(COUPS_LIB  ${SOURCE_LIB})

add_executable(main
 main.cpp 
 src/cups.h
 src/cups_board.h
 src/cups.cpp
 src/cups_board.cpp)
target_link_libraries(main ${SDL2_LIBRARIES})
target_include_directories(main PRIVATE ${SRC_DIR})

