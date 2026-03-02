cmake_minimum_required(VERSION 3.16)
project(hello_codeql VERSION 1.0.0 LANGUAGES CXX)

# ── C++ Standard ──────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Library ───────────────────────────────────────────────────
add_library(greeter_lib STATIC
    src/greeter.cpp
)
target_include_directories(greeter_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ── Main executable ───────────────────────────────────────────
add_executable(hello_app
    src/main.cpp
)
target_link_libraries(hello_app PRIVATE greeter_lib)

# ── Tests ─────────────────────────────────────────────────────
enable_testing()

add_executable(test_greeter
    tests/test_greeter.cpp
)
target_link_libraries(test_greeter PRIVATE greeter_lib)

add_test(NAME GreeterTests COMMAND test_greeter)

# ── CodeQL test files ─────────────────────────────────────────
# These are compiled so CodeQL can analyse them, but they are
# NOT registered as CTest tests (they exist only to exercise
# the custom CodeQL queries).

add_executable(test_long_function
    tests/test_long-function.cpp
)

add_executable(test_t21_operators
    tests/test_T21-require-complete-set-of-operations-for-concept.cpp
)

add_executable(test_c8_struct
    tests/test_C8-use-class-insteadof-struct.cpp
)
