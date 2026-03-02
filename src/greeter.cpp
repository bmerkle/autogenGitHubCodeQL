#include "greeter.h"

namespace hello {

std::string greet(const std::string& name) {
    if (name.empty()) {
        return "Hello, World!";
    }
    return "Hello, " + name + "!";
}

std::string version() {
    return "1.0.0";
}

} // namespace hello
