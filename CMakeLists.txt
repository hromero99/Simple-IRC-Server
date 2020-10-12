cmake_minimum_required(VERSION 3.17)
project(simple_irc)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH bin)
include_directories(include)
set(SOURCE_FILES src/)
add_executable(irc_server main_server.cpp src/server.cpp src/channel.cpp src/server_client.cpp)
add_executable(irc_client main_client.cpp src/client.cpp)