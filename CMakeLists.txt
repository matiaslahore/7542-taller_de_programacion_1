cmake_minimum_required(VERSION 2.8)

project(cmake-demo)

SET(CMAKE_CXX_FLAGS "-pthread -std=c++11 -O3")

#add_executable(ej0 client_main.cpp common_client.cpp common_client.h common_server.cpp common_server.h common_proxy_client.cpp common_proxy_client.h common_proxy_server.cpp common_proxy_server.h common_ftp.cpp common_ftp.h common_directory.cpp common_directory.h common_server_messages.cpp common_server_messages.h common_login.cpp common_login.h common_socket.cpp common_socket.h common_acceptor.cpp common_acceptor.h Lock.h)

add_executable(client client_main.cpp common_client.cpp common_client.h common_proxy_server.cpp common_proxy_server.h common_socket.cpp common_socket.h)

add_executable(server server_main.cpp common_server.cpp common_server.h common_proxy_client.cpp common_proxy_client.h common_ftp.cpp common_ftp.h common_directory.cpp common_directory.h common_server_messages.cpp common_server_messages.h common_login.cpp common_login.h common_acceptor.cpp common_acceptor.h Lock.h common_socket.cpp common_socket.h)