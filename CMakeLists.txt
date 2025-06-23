cmake_minimum_required(VERSION 3.10)

project(EscapeGame
    VERSION 1.0
    DESCRIPTION "A library for walking through large files"
    LANGUAGES CXX
)

add_library(EscapeGameLib
    escaper/Escaper.cpp
    hunter/hunter.cpp
    )


target_include_directories(EscapeGameLib PUBLIC 
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/DataProvider
    ${CMAKE_SOURCE_DIR}/EncodingFixer
    ${CMAKE_SOURCE_DIR}/FileReverser)

add_executable(EscapeGameTest main.cpp)
target_link_libraries(EscapeGameTest PRIVATE EscapeGameLib)
