# tmail-relay setup
## tmail-relay include directores
file(GLOB TMAIL_RELAY_SRCS "*.c")
add_executable(tmail-relay ${TMAIL_RELAY_SRCS})
message(STATUS "GLOBAL: ${CMAKE_SOURCE_DIR}")
target_include_directories(tmail-relay PRIVATE "relay/include/" "${CMAKE_SOURCE_DIR}/include")

# wolfSSL Setup
## Use wolfSSL user settings
target_compile_definitions(tmail-relay PRIVATE WOLFSSL_USER_SETTINGS)
## Include and link wolfSSL
target_include_directories(tmail-relay PRIVATE ${WOLFSSL_INCLUDE_DIRS})
target_link_libraries(tmail-relay PRIVATE ${WOLFSSL_LIBRARIES})
## WolfSSL requires winsock to be linked for static builds
target_link_libraries(tmail-relay PRIVATE ws2_32)

add_custom_command(
    TARGET tmail-relay
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_SOURCE_DIR}/certs"
        "${CMAKE_BINARY_DIR}/relay/Debug/certs"
)