# tmail-client setup
## tmail-client include directores
file(GLOB TMAIL_CLIENT_SRCS "*.c")
add_executable(tmail-client ${TMAIL_CLIENT_SRCS})
target_include_directories(tmail-client PRIVATE "client/include/" "${CMAKE_SOURCE_DIR}/include")

# wolfSSL Setup
## Use wolfSSL user settings
target_compile_definitions(tmail-client PRIVATE WOLFSSL_USER_SETTINGS)
## Include and link wolfSSL
target_include_directories(tmail-client PRIVATE ${WOLFSSL_INCLUDE_DIRS})
target_link_libraries(tmail-client PRIVATE ${WOLFSSL_LIBRARIES})
## WolfSSL requires winsock to be linked for static builds
target_link_libraries(tmail-client PRIVATE ws2_32)

add_custom_command(
    TARGET tmail-client
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_SOURCE_DIR}/certs"
        "${CMAKE_BINARY_DIR}/client/Debug/certs"
)