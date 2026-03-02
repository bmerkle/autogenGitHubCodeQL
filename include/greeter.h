#ifndef GREETER_H
#define GREETER_H

#include <string>

namespace hello {

/// Returns a greeting message for the given name.
std::string greet(const std::string& name);

/// Returns the program version string.
std::string version();

} // namespace hello

#endif // GREETER_H
