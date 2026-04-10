# QwenCalc

A modern desktop calculator tool built with C++ and Qt.

## Features

- **Basic Arithmetic**: Addition, subtraction, multiplication, division, and modulo
- **Advanced Functions**: Trigonometric (sin, cos, tan), logarithmic (log, ln), square root, power, and factorial
- **History Tracking**: Keeps track of all calculations with expression and results
- **Memory Functions**: Store, recall, add, and subtract from memory
- **Modern UI**: Qt-based graphical interface with keyboard shortcuts
- **Theme Support**: Light and dark themes with customizable colors

## Project Structure

```
qwencalc/
├── CMakeLists.txt          # Main CMake configuration
├── backend/                # Core calculation logic
│   ├── ExpressionParser.h/cpp
│   ├── CalculatorEngine.h/cpp
│   └── HistoryManager.h/cpp
├── frontend/               # Qt-based UI
│   ├── CalculatorWindow.h/cpp
│   ├── DisplayWidget.h/cpp
│   ├── KeypadWidget.h/cpp
│   └── ThemeManager.h/cpp
├── src/                    # Main application entry
│   └── main.cpp
├── tests/                  # Unit and integration tests
│   ├── test_*.cpp
│   └── CMakeLists.txt
├── docs/                   # Documentation
│   └── API.md
└── README.md
```

## Installation

### Prerequisites

- CMake 3.16 or higher
- Qt6 (Widgets module)
- C++17 compiler (GCC, Clang, or MSVC)

### Build Instructions

```bash
# Create build directory
mkdir build && cd build

# Configure
cmake ..

# Build
make -j$(nproc)

# Run
./qwencalc
```

### On Windows

```bash
mkdir build && cd build
cmake .. -G Ninja
nmake qwencalc
```

### On macOS

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/lib/cmake/Qt6
make -j$(nproc)
```

## Usage

### Basic Operations

```
1 + 2 = 3
10 * 5 = 50
20 / 4 = 5
10 % 3 = 1
```

### Advanced Functions

```
sin(90) = 1 (in degrees)
cos(0) = 1
tan(45) = 1
sqrt(16) = 4
log(100) = 2 (base 10)
ln(e) = 1 (natural log)
pow(2, 3) = 8
factorial(5) = 120
```

### Memory Functions

- **M+**: Add current result to memory
- **M-**: Subtract current result from memory  
- **MR**: Recall memory value
- **MS**: Store current result to memory

### Keyboard Shortcuts

- Numbers 0-9: Enter numbers
- +, -, *, /: Enter operators
- Enter: Calculate result
- Backspace: Delete last character
- Escape: Clear display
- m: Memory add
- n: Memory subtract
- r: Memory recall
- s: Memory store

## Building from Subagent

### Backend Logic Agent

The backend consists of three main components:

1. **ExpressionParser** - Mathematical expression parsing with support for:
   - Standard arithmetic operators
   - Trigonometric functions
   - Logarithmic functions
   - Factorial
   - Parentheses and scientific notation

2. **CalculatorEngine** - Core calculation logic with:
   - Precision control
   - Error handling
   - Result caching

3. **HistoryManager** - Calculation history tracking:
   - Stores expression-result pairs
   - Configurable history limit
   - Export history functionality

### Frontend UI Agent

The Qt-based UI consists of:

1. **CalculatorWindow** - Main application window
2. **DisplayWidget** - Result and expression display
3. **KeypadWidget** - Numeric keypad with function buttons
4. **ThemeManager** - Theme and color management

### Testing Agent

Unit tests cover:
- ExpressionParser accuracy
- Edge cases (division by zero, overflow)
- Function correctness
- Integration tests

### Build & Deployment Agent

CMake configuration includes:
- Cross-platform support
- Qt6 integration
- Test framework setup
- CI/CD ready

## License

MIT License

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.
