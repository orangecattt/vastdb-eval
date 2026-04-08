# CMakeLists.txt for minimal reproducible example
# Build with: cmake . && make

cmake_minimum_required(VERSION 3.10)
project(vim_dialog_changed)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(good OBJECT good.cpp)
