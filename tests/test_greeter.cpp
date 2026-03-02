#include <cassert>
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include "greeter.h"

// Minimal test framework — no external dependencies needed
static int tests_run = 0;
static int tests_passed = 0;

static void run_test(const char* name, std::function<bool()> fn) {
    ++tests_run;
    std::cout << "  " << name << " ... ";
    if (fn()) {
        ++tests_passed;
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
}

int main() {
    std::cout << "Running tests..." << std::endl;

    // Test 1: greet with empty string returns default greeting
    run_test("greet_empty_returns_hello_world", [] {
        std::string result = hello::greet("");
        return result == "Hello, World!";
    });

    // Test 2: greet with a name returns personalised greeting
    run_test("greet_name_returns_personalised", [] {
        std::string result = hello::greet("Alice");
        return result == "Hello, Alice!";
    });

    // Test 3: version returns expected format
    run_test("version_returns_semver", [] {
        std::string v = hello::version();
        return v.find('.') != std::string::npos;
    });

    // Test 4: greet with special characters
    run_test("greet_special_characters", [] {
        std::string result = hello::greet("C++");
        return result == "Hello, C++!";
    });

    // Summary
    std::cout << std::endl;
    std::cout << tests_passed << " / " << tests_run << " tests passed." << std::endl;

    return (tests_passed == tests_run) ? 0 : 1;
}
