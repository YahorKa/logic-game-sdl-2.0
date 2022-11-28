cmake_minimum_required(VERSION 2.8)
project(Cupboards)

set(CMAKE_CXX_STANDARD 17)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCE_LIB  ${SRC_DIR}/cup.h)
#include_directories(src)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
#add_library(COUPS_LIB  ${SOURCE_LIB})

add_executable(main
 main.cpp 
 src/cup.h
 src/cups_board.h
 src/cup.cpp
 src/cups_board.cpp
 src/defines.h
 src/file_manager.h
 src/file_manager.cpp)
target_link_libraries(main ${SDL2_LIBRARIES})
target_include_directories(main PRIVATE ${SRC_DIR})

