
#include <concepts>

///////////////////////////////////////////////
//bad example
///////////////////////////////////////////////

template<typename T> concept Subtractable = requires(T a, T b) { a - b; };

///////////////////////////////////////////////
//minimal example
///////////////////////////////////////////////
class Minimal {
    // ...
};

bool operator==(const Minimal&, const Minimal&);
bool operator<(const Minimal&, const Minimal&);

Minimal operator+(const Minimal&, const Minimal&);
// no other operators

void f_minimal(const Minimal& x, const Minimal& y)
{
    if (!(x == y)) { /* ... */ }    // OK
    if (x != y) { /* ... */ }       // surprise! error

    while (!(x < y)) { /* ... */ }  // OK
    while (x >= y) { /* ... */ }    // surprise! error

    x = x + y;          // OK
    x += y;             // surprise! error
}

///////////////////////////////////////////////
// convient example
///////////////////////////////////////////////
class Convenient {
    // ...
};

bool operator==(const Convenient&, const Convenient&);
bool operator<(const Convenient&, const Convenient&);
// ... and the other comparison operators ...

Convenient operator+(const Convenient&, const Convenient&);
// ... and the other arithmetic operators ...

void f(const Convenient& x, const Convenient& y)
{
    if (!(x == y)) { /* ... */ }    // OK
    if (x != y) { /* ... */ }       // OK

    while (!(x < y)) { /* ... */ }  // OK
    while (x >= y) { /* ... */ }    // OK

    x = x + y;     // OK
    x += y;        // OK
}
