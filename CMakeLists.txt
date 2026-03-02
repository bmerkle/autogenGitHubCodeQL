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
