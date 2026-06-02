cmake_minimum_required(VERSION 3.20)

project(InlinerPass)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(InlinerPass SHARED src/InlinerPass.cpp)
