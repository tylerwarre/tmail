cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_COMPILER cl)
set(CMAKE_CXX_COMPILER cl)

# Load custom cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# Identify where wolfSSL libraries and headers are stored
set(WOLFSSL_LIBRARY "C:/Users/M83393/libs/wolfssl/Release/x64/wolfssl.lib")
set(WOLFSSL_INCLUDE_DIR "C:/Users/M83393/libs/wolfssl/")

project(tmail)

find_package(WolfSSL REQUIRED)

# tmail-relay setup
## tmail-relay include directores
file(GLOB TMAIL_RELAY_SRCS "relay/*.c")
add_executable(tmail-relay ${TMAIL_RELAY_SRCS})
target_include_directories(tmail-relay PRIVATE "relay/include/" "include/")

# wolfSSL Setup
## Use wolfSSL user settings
target_compile_definitions(tmail-relay PRIVATE WOLFSSL_USER_SETTINGS)
## Include and link wolfSSL
target_include_directories(tmail-relay PRIVATE ${WOLFSSL_INCLUDE_DIRS})
target_link_libraries(tmail-relay PRIVATE ${WOLFSSL_LIBRARIES})
## WolfSSL requires winsock to be linked for static builds
target_link_libraries(tmail-relay PRIVATE ws2_32)