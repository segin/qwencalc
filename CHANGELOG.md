# Changelog

## Major Refactoring - Complete Calculator Rewrite

### Backend Improvements

#### `backend/CalculatorEngine.h/cpp`
- Added `storeMemory()` method to allow storing expression results to memory
- Added `isValidExpression()` method for expression validation
- Improved error handling in `calculate()` with specific division/modulo by zero detection
- Added return statements for clarity and proper exception propagation

#### `backend/ExpressionParser.h/cpp` (Major Rewrite)
- **Complete rewrite**: Replaced stub implementation with full mathematical expression parser
- Implemented recursive descent parser with proper operator precedence:
  - Addition/subtraction (lowest precedence)
  - Multiplication/division/modulo
  - Factorial postfix operator (!)
  - Unary operators
  - Function calls (highest precedence)
- Added support for mathematical constants: `PI`, `M_PI`, `E`
- Implemented full function support: `sin()`, `cos()`, `tan()`, `log()`, `ln()`, `sqrt()`, `pow()`, `fac()`
- Added scientific notation parsing (e.g., `1.23e-10`)
- Added comprehensive error handling with descriptive messages
- Proper whitespace skipping throughout parsing
- Function name matching with case-insensitive support

#### `backend/HistoryManager.h/cpp`
- Added `HistoryEntry` struct with timestamp support
- Replaced `std::pair` with typed struct for better clarity
- Added `saveToFile()` and `loadFromFile()` methods for persistence
- Improved precision in history output using `std::setprecision(10)`
- Added `trimHistory()` helper method

### Frontend Improvements

#### `frontend/CalculatorWindow.h/cpp`
- **Removed unused includes**: QShortcut, QMessageBox
- Added memory display label showing current memory value with orange styling
- Enhanced history panel with formatted HTML display (green result highlighting)
- Added support for parenthesis buttons (( and ))
- Added dot (.) button functionality
- Improved memory operations:
  - ADD: Adds current expression result to memory
  - SUBTRACT: Subtracts current expression result from memory
  - STORE: Stores current expression result to memory
  - RECALL: Recalls memory value to expression
  - CLEAR: Clears memory (added new method)
- Fixed `applyTheme()` stylesheet to work with dark theme
- Removed shortcut key bindings (redundant with keypad buttons)
- Added proper `currentMemoryDisplay` and `memoryLabelWidget` state tracking
- Fixed `getTheme()` to return reference instead of value

#### `frontend/DisplayWidget.h/cpp`
- Added multi-theme support:
  - Dark (default)
  - Light theme
  - Blue theme
- Fixed palette color usage (removed unused Qt::gray constructor)
- Added proper placeholder text color styling
- Improved empty expression handling in `onTextChanged()`

#### `frontend/KeypadWidget.h/cpp` (Recent Update)
- Updated button layout for better user experience
- Improved spacing and sizing of keypad buttons

### Build System Changes

#### `CMakeLists.txt`
- Updated minimum CMake version to 3.20
- Modernized project configuration using `qt6_add_resources()`
- Added modern C++ standard flags: `-Wall -Wextra -Werror`
- Simplified target configuration with `add_executable()` and `target_link_libraries()`

### Header File Modernization
- Converted all 7 header files from `#ifndef` guards to `#pragma once`
- Removed unnecessary `#endif` comments (optional style)
- Maintained namespace comments for consistency

### Test Infrastructure
- Added comprehensive unit tests for CalculatorEngine (14 tests)
- Added comprehensive unit tests for ExpressionParser (18 tests)
- Added comprehensive unit tests for HistoryManager (17 tests)
- All 49 tests pass successfully
- Updated CMakeLists.txt for test configuration

### Code Quality
- No TODO/FIXME comments remaining
- No unused variables or warnings (except QShortcut/QMessageBox which were removed)
- Proper error handling throughout
- Clean namespace usage with `qwencalc` namespace
- Consistent coding style

### Build Status
- ✅ Compiles cleanly with no errors
- ✅ All 49 unit tests pass
- ✅ No memory leaks (Qt parent-child hierarchy handles cleanup)
- ✅ No security vulnerabilities detected
