# Hello CodeQL — C++ Demo Project

A minimal C++ project that demonstrates:

| Feature | Details |
|---|---|
| **Language** | C++17 |
| **Build system** | CMake ≥ 3.16 |
| **Platforms** | Windows 11 (MSVC 2022) · Ubuntu (Clang) |
| **CI** | GitHub Actions |
| **Static analysis** | GitHub CodeQL (`security-and-quality` suite) |

## Project layout

```
├── include/
│   └── greeter.h            # public header
├── src/
│   ├── greeter.cpp          # library implementation
│   └── main.cpp             # application entry point
├── tests/
│   └── test_greeter.cpp     # unit tests
├── .github/workflows/
│   ├── ci.yml               # build & test (MSVC + Clang)
│   └── codeql.yml           # CodeQL static analysis
└── CMakeLists.txt           # build configuration
```

## Building locally

### Windows (MSVC)

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
ctest --test-dir build --build-config Release --output-on-failure
```

### Ubuntu / macOS (Clang)

```bash
cmake -S . -B build \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

## GitHub Actions

### CI Build & Test (`ci.yml`)

Triggers on every push/PR to `main`. Builds and runs tests on:

* **Windows** – `windows-latest` with MSVC (Visual Studio 2022)
* **Ubuntu** – `ubuntu-latest` with Clang

### CodeQL Analysis (`codeql.yml`)

Runs the **`security-and-quality`** query suite from the CodeQL framework
on every push/PR and on a weekly schedule. This suite includes standard
C++ rules such as:

| Rule ID | Description |
|---|---|
| `cpp/uninitialized-local` | Use of uninitialized variables |
| `cpp/overflow-buffer` | Buffer overflows |
| `cpp/null-dereference` | Null-pointer dereferences |
| `cpp/missing-return` | Missing return statements |
| `cpp/resource-not-released-in-destructor` | Resource leaks |

Results appear in the repository's **Security → Code scanning alerts** tab.

## License

See [LICENSE](LICENSE).
