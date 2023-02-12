cmake_minimum_required(VERSION 3.23)
project(sql)

set(CMAKE_CXX_STANDARD 14)

add_executable(sql main.cpp)
target_link_libraries(sql C:/Windows/System32/odbc32.dll)