# user-auth-c

Small C library for operator login, usernames, session tokens and audit logging, with a CMake + CTest test suite.

**Demo target for Proof Patch: intentionally contains security bugs. Never deploy this code.**

| Area | Vulnerability | CWE |
|---|---|---|
| `admin_login` | Hardcoded admin password in the source | CWE-798 |
| `set_username` | `strcpy` into a 16-byte buffer: buffer overflow | CWE-120 |
| `new_session_token` | Tokens from `srand(time(NULL))` + `rand()`: predictable sessions | CWE-338 |
| `audit` | User text used as the `fprintf` format: format-string bug | CWE-134 |

Run the tests: `cmake -S . -B build && cmake --build build && ctest --test-dir build`.
