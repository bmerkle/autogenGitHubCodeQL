// ──────────────────────────────────────────────────────────────
// Test file for T21 — incomplete operator sets
//
// CodeQL analyses the CLASS DECLARATIONS and their operator
// overloads.  It does NOT need to compile expressions that use
// the missing operators.  The comments below show what would
// fail at compile time if you tried to use the incomplete API.
// ──────────────────────────────────────────────────────────────

///////////////////////////////////////////////
// BAD example — incomplete operator set
//   (should trigger CodeQL warning)
///////////////////////////////////////////////

class Minimal {
    int value;
public:
    Minimal(int v) : value(v) {}
    int getValue() const { return value; }
};

// Only operator== and operator< — missing !=, >, <=, >=
bool operator==(const Minimal& a, const Minimal& b) { return a.getValue() == b.getValue(); }
bool operator<(const Minimal& a, const Minimal& b)  { return a.getValue() <  b.getValue(); }

// Only operator+ — missing operator-
Minimal operator+(const Minimal& a, const Minimal& b) { return Minimal(a.getValue() + b.getValue()); }

// The following calls would FAIL to compile because the operators are missing:
//   if (x != y) { /* ... */ }       // error: no operator!=
//   while (x >= y) { /* ... */ }    // error: no operator>=
//   x += y;                         // error: no operator+=

///////////////////////////////////////////////
// GOOD example — complete operator set
//   (should NOT trigger CodeQL warning)
///////////////////////////////////////////////

class Convenient {
    int value;
public:
    Convenient(int v) : value(v) {}
    int getValue() const { return value; }
};

// Complete comparison set
bool operator==(const Convenient& a, const Convenient& b) { return a.getValue() == b.getValue(); }
bool operator!=(const Convenient& a, const Convenient& b) { return !(a == b); }
bool operator<(const Convenient& a, const Convenient& b)  { return a.getValue() <  b.getValue(); }
bool operator>(const Convenient& a, const Convenient& b)  { return b < a; }
bool operator<=(const Convenient& a, const Convenient& b) { return !(b < a); }
bool operator>=(const Convenient& a, const Convenient& b) { return !(a < b); }

// Complete arithmetic set
Convenient operator+(const Convenient& a, const Convenient& b) { return Convenient(a.getValue() + b.getValue()); }
Convenient operator-(const Convenient& a, const Convenient& b) { return Convenient(a.getValue() - b.getValue()); }

// These all compile fine:
void f(const Convenient& x, const Convenient& y) {
    if (x != y) { /* OK */ }
    while (x >= y) { /* OK */ }
    Convenient z = x + y;  // OK
    Convenient w = x - y;  // OK
}
