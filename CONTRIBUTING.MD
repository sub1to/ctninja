# Contributing to CTNinja  
Thank you for considering contributing! Below are guidelines to ensure consistency and quality.  

---

## Code Style  
- **C++20**: Use modern features (`consteval`, concepts, etc.) where appropriate.  
- **Naming Conventions**:  
  - `snake_case` for functions/variables (e.g., `get_module`).  
  - `PascalCase` for classes/templates (e.g., `SecureValue64`).  
  - `UPPER_SNAKE_CASE` for macros (e.g., `CTNINJA_MAGIC_IMPORT`).  
- **Formatting**:  
  - 4-space indentation, `{}` braces always.  
  - Header guards: prefer `#ifndef` over `#pragma once`.  
- **Comments**:  
  - yes

---

## Building & Testing  
- **Premake5**: Build files are generated via `premake5.lua` – do not commit IDE-specific files.  
- **Unit Tests**:  
  - Add tests for new features in `cttest/` (using your existing framework).  

---

## Submitting Changes  
1. **Fork** the repository and create a feature branch.  
2. **Test**: Ensure all existing tests pass and add new ones for your changes.  
3. **PR Template**:  
   - Describe **what** and **why** (not just "how").  
   - Note any impacts on obfuscation strength or performance.  

---

## Code of Conduct  
Be respectful and constructive. Security-related projects require extra care – avoid "quick hacks" that compromise reliability.  