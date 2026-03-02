#include <iostream>
#include "greeter.h"

int main() {
    std::cout << hello::greet("") << std::endl;
    std::cout << hello::greet("GitHub CodeQL") << std::endl;
    std::cout << "Version: " << hello::version() << std::endl;
    return 0;
}
