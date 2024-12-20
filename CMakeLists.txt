cmake_minimum_required(VERSION 3.20)
project(GA_Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(/W3 /WX)

add_subdirectory(Engine)
add_subdirectory(Game)

