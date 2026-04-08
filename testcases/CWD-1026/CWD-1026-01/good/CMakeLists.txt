cmake_minimum_required(VERSION 3.10)
project(vim_cve_2024_41957 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(good STATIC good.cpp)
target_compile_options(good PRIVATE -Wall -Wextra)
