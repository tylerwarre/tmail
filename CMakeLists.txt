cmake_minimum_required(VERSION 3.29.2)

project(tmail)

find_package(wolfssl CONFIG REQUIRED)
add_executable(tmail src/test.c)

target_compile_options(tmail PRIVATE /std:clatest)

target_link_libraries(tmail PRIVATE wolfssl::wolfssl)
target_include_directories(tmail PRIVATE ${WOLFSSL_INCLUDE_DIRS})