# CTNinja: Compile-Time Ninja  

**Compile-time string encryption and import obfuscation for Windows PE32(+) binaries**  

<div align="center">
  <a style="margin: 2px;">
    <img alt="LICENSE-MIT" src="https://img.shields.io/badge/language-C%2B%2B20-blue?logo=C%2B%2B">
  </a>
  <a href="https://github.com/sub1to/ctninja/blob/public/LICENSE.MD" style="margin: 2px;">
    <img alt="LICENSE-MIT" src="https://img.shields.io/badge/LICENSE-MIT-green">
  </a>
</div>

---

## Features  
- 🔒 **Compile-Time String Encryption**  
  Obfuscate strings at compile-time using the `_X` operator to avoid plaintext exposure in binaries.  
  ```cpp
  auto str = "SensitiveData"_X; // Encrypted at compile-time
  printf(str.c_str());
  ```
  
- 🎯 **JOAAT Hashing**  
  Generate Jenkins One-At-A-Time (JOAAT) hashes at compile-time (`_JOAAT`/`_JOAAT64`) or runtime (`joaat`/`wjoaat`/`joaat64`/`wjoaat64`).  
  ```cpp
  constexpr auto hash32 = "Kernel32.dll"_JOAAT;   // Compile-time hash
  constexpr auto hash64 = "Kernel32.dll"_JOAAT64; // Compile-time hash
  ```

- 🕵️ **PEB Walking & Stealthy Imports**  
  Resolve modules and exports without `GetProcAddress` or static imports:  
  ```cpp
  auto hModule = ctninja::xport::get_module("Kernel32.dll"_JOAAT);
  auto pFunc   = ctninja::xport::get_export(hModule, "CloseHandle"_JOAAT);
  ```

- 💻 **Operator-Driven Function Calls**  
  Call obfuscated imports directly via the `$$` syntax:  
  ```cpp
  // Predefined in def.h: fpCreateThread, fpLoadLibraryA, fpCloseHandle, etc.
  $$(Kernel32.dll, CloseHandle, m_hPipeThread); // Resolves and calls at runtime
  ```
  
- 🛡️ **Secure Runtime Value Obfuscation**  
  Protect in-memory values with XOR + bit rotation using `SecureValue32`/`SecureValue64`. Keys are re-rolled on every access. 
  Most operators are implemented, and it will implicitly cast to it's template type, allowing you to use SecureValue as if
  it is a built-in type.
  

- **PE32+ Focus**  
  Built for modern Windows binaries, with minimal overhead.

---

## Installation  
CTNinja is built using **Premake5**. Follow these steps:  

1. **Generate Project Files**  
   Run `build.bat` (Visual Studio 2022) or `premake5 vs2022`. 

2. **Build the Library**  
   Compile the generated project to produce `ctninja.lib`.  

3. **Link in Your Project**  
   Add `ctninja.lib` and include the `ctninja.h` header.  


---

## Usage  
### 1. Obfuscate Strings  
```cpp
#include <ctninja/ctninja.h>

printf("Hello, Malware Analyst"_X.c_str());
```

⚠️ **Critical**:  
Do not call `c_str()` multiple times on the same object!

The data is decrypted on the stack when you call `c_str()`. Calling it again will re-encrypt the data.

- ❌
   ```cpp
   auto str = "SensitiveData"_X; // Encrypted at compile-time
   printf(str.c_str());
   printf(str.c_str());
   ```
- ✅
   ```cpp
   auto secstr = "SensitiveData"_X; // Encrypted at compile-time
   auto str = secstr.c_str();
   printf(str);
   printf(str);
   ```
- ✅
   ```cpp
   printf("SensitiveData"_X.c_str());
   printf("SensitiveData"_X.c_str());
   ```

### 2. Resolve Modules/Exports via PEB  
```cpp
#include <ctninja/ctninja.h>

HMODULE  hKernel32      = ctninja::xport::get_module("Kernel32.dll"_JOAAT);
FARPROC  pCreateFile    = ctninja::xport::get_export(hKernel32, "CreateFileW"_JOAAT);
```

### 3. Call Functions Stealthily  
```cpp
#define CTNINJA_MAGIC_IMPORT
#include <ctninja/ctninja.h>

HANDLE   hFile          = $$(Kernel32.dll, CreateFileW, L"file.txt", GENERIC_READ, ...);
```

#### 3.1 Defining Function Signatures  
For `$$()` to work, **you must define the function signature** as `fp<FunctionName>` in your code.  
Predefined signatures for common Windows APIs (e.g., `fpCreateThread`, `fpLoadLibraryA`) are in [`ctninja/include/def.h`](include/def.h).  

For custom functions, define the typedef **before using `$$()`**:  
```cpp
// Example for a custom function
typedef BOOL (WINAPI* fpSomeObscureFunction)(DWORD param1, LPCSTR param2);
// Now call it via:
$$(SomeDll.dll, SomeObscureFunction, 123, "param");
```

⚠️ **Critical**:  
- The typedef **must** match the exact function signature.  
- The naming convention **must** be `fp<FunctionName>` (case-sensitive).  


### 4. JOAAT Hashing  

#### 4.1 Compile-Time JOAAT Hashing  
```cpp
#include <ctninja/ctninja.h>

u32      ulHash32       = "hash_me"_JOAAT;     // Compile-Time JOAAT for static strings
u64      ulHash64       = "hash_me"_JOAAT64;   // Compile-Time JOAAT64 for static strings
```

#### 4.2 Runtime JOAAT Hashing  
```cpp
#include <ctninja/ctninja.h>

u32      ulHash32       = ctninja::joaat("hash_me");     // Runtime JOAAT for dynamic strings
u64      ulHash64       = ctninja::wjoaat64(L"hash_me"); // Runtime JOAAT64 for dynamic strings
```


### 5. Protect Sensitive Values in Memory

#### 5.1 float
```cpp
#include <ctninja/ctninja.h>

typedef ctninja::SecureValue32<float> SV_Float;

SV_Float secretFloat = 123.45f; // Stored encrypted in memory

// Use like a normal value (automatically encrypts/decrypts):
secretFloat += 10.0f;
printf("%f", (float)secretFloat);
```

#### 5.2 BYTE*
```cpp
#include <ctninja/ctninja.h>

// Architecture-agnostic definition (auto-chooses 32/64-bit)
#ifdef _M_X64
typedef ctninja::SecureValue64<BYTE*> SVP_BYTE;
#else
typedef ctninja::SecureValue32<BYTE*> SVP_BYTE;
#endif

SVP_BYTE pSec;

pSec    = pArray;
*pSec	= 0x1f;
pSec[1]	= 0x2e;
```

---

## Notes  
- **Windows Only**: Designed for PE32(+) binaries (x86/x64).  
- **C++20 Required**: Relies on `constexpr`/`consteval` for compile-time magic.  
- **Antivirus Warnings**: Obfuscation may trigger heuristic detections. Test thoroughly.  

---

## Authors  
- **sub1to** - *Initial work* - [sub1to](https://github.com/sub1to)  
  
See also the list of [contributors](https://github.com/sub1to/ctninja/contributors) who participated in this project.  

## License  
MIT License. See [LICENSE.MD](LICENSE.MD)

## Contributing  
PRs and issues welcome! See [CONTRIBUTING.MD](CONTRIBUTING.MD) for guidelines.  