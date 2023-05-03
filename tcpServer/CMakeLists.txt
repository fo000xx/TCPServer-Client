cmake_minimum_required(VERSION 3.25.2)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(tcpServer)
add_executable(tcpServer main.cpp tcpServer.cpp tcpConnection.cpp)