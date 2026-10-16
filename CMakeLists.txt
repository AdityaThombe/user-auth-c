cmake_minimum_required(VERSION 3.16)
project(user_auth C)

set(CMAKE_C_STANDARD 11)

add_library(userauth src/auth.c)
target_include_directories(userauth PUBLIC include)

enable_testing()
add_executable(test_auth tests/test_auth.c)
target_link_libraries(test_auth userauth)
add_test(NAME admin_login_ok COMMAND test_auth login_ok)
add_test(NAME admin_login_rejects_wrong_password COMMAND test_auth login_bad)
add_test(NAME stores_short_username COMMAND test_auth username)
add_test(NAME session_token_has_32_hex_chars COMMAND test_auth token)
add_test(NAME audit_message_is_written COMMAND test_auth audit)
