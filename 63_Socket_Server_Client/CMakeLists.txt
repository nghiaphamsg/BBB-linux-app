cmake_minimum_required(VERSION 3.19)
project(socket_client_server)

# Include path
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Include header & source
add_library(
    client-server
    include/SocketClient.h
    include/SocketClient.cpp
    include/SocketServer.h
    include/SocketServer.cpp
)

# Compile area
add_executable(client client.cpp)
add_executable(server server.cpp)

# Linker library
target_link_libraries(client PRIVATE client-server)
target_link_libraries(server PRIVATE client-server)

# Properties
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)