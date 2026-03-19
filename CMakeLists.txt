cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_COMPILER cl)
set(CMAKE_CXX_COMPILER cl)

# Load custom cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# Identify where wolfSSL libraries and headers are stored
set(WOLFSSL_LIBRARY "$ENV{WOLFSSL_ROOT}/Release/x64/wolfssl.lib")
set(WOLFSSL_INCLUDE_DIR "$ENV{WOLFSSL_ROOT}")

project(tmail)

find_package(WolfSSL REQUIRED)

add_subdirectory(relay)