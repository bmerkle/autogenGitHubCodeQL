// ──────────────────────────────────────────────────────────────
// Test file for C8 — Use class instead of struct if any member
// is non-public.
//
//   CONFORM  = all members are public  → no CodeQL warning
//   VIOLATE  = has private/protected   → CodeQL warning
// ──────────────────────────────────────────────────────────────

// ═══════════════════════════════════════════════════════════════
//  CONFORMING examples (should NOT trigger the rule)
// ═══════════════════════════════════════════════════════════════

// 1. Plain data struct — everything public (default for struct)
struct GoodPlainData {
    int x;
    int y;
};

// 2. Struct with public member function
struct GoodWithFunction {
    int value;
    void print() const {}
};

// 3. Empty struct
struct GoodEmpty {};

// 4. Struct with only public members explicitly marked
struct GoodExplicitPublic {
public:
    int a;
    void doSomething() {}
};

// ═══════════════════════════════════════════════════════════════
//  VIOLATING examples (SHOULD trigger the rule)
// ═══════════════════════════════════════════════════════════════

// 5. Struct with a private member variable
struct BadPrivateVariable {
private:
    int secret;
public:
    int x;
};

// 6. Struct with a protected member variable
struct BadProtectedVariable {
protected:
    int internal_value;
public:
    int getId() const { return internal_value; }
};

// 7. Struct with a private member function
struct BadPrivateFunction {
    int data;
private:
    void helperFunc() {}
};

// 8. Struct with a protected member function
struct BadProtectedFunction {
    int data;
protected:
    void onEvent() {}
};

// 9. Struct with both private variable and private function
struct BadFullyPrivate {
private:
    int x;
    void compute() {}
public:
    int getX() const { return x; }
};

int main() {
    return 0;
}
