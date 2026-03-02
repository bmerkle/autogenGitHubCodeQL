// ──────────────────────────────────────────────────────────────
// Test file for long-function.ql (custom-cpp/long-function)
//
//   function_a_short  — CONFORMS   (< 50 lines of code)
//   function_b_long   — VIOLATES   (> 50 lines of code)
// ──────────────────────────────────────────────────────────────
#include <iostream>

// ── Function A: short function (< 50 lines) — should PASS ───
int function_a_short(int x) {
    int result = 0;
    result += x * 1;
    result += x * 2;
    result += x * 3;
    result += x * 4;
    result += x * 5;
    result += x * 6;
    result += x * 7;
    result += x * 8;
    result += x * 9;
    result += x * 10;
    std::cout << "Result: " << result << std::endl;
    return result;
}

// ── Function B: long function (> 50 lines) — should FAIL ────
int function_b_long(int x) {
    int result = 0;
    result += x * 1;
    result += x * 2;
    result += x * 3;
    result += x * 4;
    result += x * 5;
    result += x * 6;
    result += x * 7;
    result += x * 8;
    result += x * 9;
    result += x * 10;
    result += x * 11;
    result += x * 12;
    result += x * 13;
    result += x * 14;
    result += x * 15;
    result += x * 16;
    result += x * 17;
    result += x * 18;
    result += x * 19;
    result += x * 20;
    result += x * 21;
    result += x * 22;
    result += x * 23;
    result += x * 24;
    result += x * 25;
    result += x * 26;
    result += x * 27;
    result += x * 28;
    result += x * 29;
    result += x * 30;
    result += x * 31;
    result += x * 32;
    result += x * 33;
    result += x * 34;
    result += x * 35;
    result += x * 36;
    result += x * 37;
    result += x * 38;
    result += x * 39;
    result += x * 40;
    result += x * 41;
    result += x * 42;
    result += x * 43;
    result += x * 44;
    result += x * 45;
    result += x * 46;
    result += x * 47;
    result += x * 48;
    result += x * 49;
    result += x * 50;
    result += x * 51;
    std::cout << "Result: " << result << std::endl;
    return result;
}

int main() {
    function_a_short(2);
    function_b_long(2);
    return 0;
}