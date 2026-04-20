# ARCHITECTURE.md

## 1. Project Structure

```
[Project Root]/
├── src/              # Application entry point
│   └── main.cpp      # Qt application initialization
├── backend/          # Core calculator logic
│   ├── CalculatorEngine.h/.cpp
│   ├── ExpressionParser.h/.cpp
│   └── HistoryManager.h/.cpp
├── frontend/         # Qt6 GUI components
│   ├── CalculatorWindow.h/.cpp
│   ├── DisplayWidget.h/.cpp
│   ├── KeypadWidget.h/.cpp
│   └── ThemeManager.h/.cpp
├── tests/            # Unit and integration tests
│   ├── test_CalculatorEngine.cpp
│   ├── test_ExpressionParser.cpp
│   ├── test_HistoryManager.cpp
│   └── test_integration.cpp
├── build/            # Build directory
├── CMakeLists.txt    # CMake configuration
├── .gitignore        # Git ignore rules
├── REQUIREMENTS.md   # Requirements document
├── PLAN.md           # Project plan with milestones
└── ARCHITECTURE.md   # This document
```

## 2. High-Level System Diagram

```
[User] --> [QwenCalc (Qt6 GUI)]
                   |
                   +--> [Calculator Engine]
                   |       +--> [Expression Parser]
                   |       +--> [History Manager]
                   |       +--> [Memory Management]
                   |
                   +--> [UI Display]
                   |       +--> [Formula Display]
                   |       +--> [Result Display]
                   |
                   +--> [Keypad Input]
                   |       +--> [Numeric Buttons]
                   |       +--> [Operators]
                   |       +--> [Functions]
                   |
                   +--> [History Panel]
                   |       +--> [Calculation Log]
                   |       +--> [Click-to-Reuse]
                   |
                   +--> [Theme Manager]
```

## 3. Core Components

### 3.1. CalculatorWindow

**Name:** Main Window and Application Controller

**Description:** The central UI component that manages the calculator interface, handles user input, and coordinates between the display, keypad, and engine components.

**Technologies:** C++ (Qt6), QMainWindow, QScrollArea

**Deployment:** Local desktop application

**Responsibilities:**
- Window management and layout
- User input handling (mouse and keyboard)
- Signal/slot connections between UI components
- Theme switching (light/dark modes)
- History panel display and interaction
- Settings persistence (load on startup, save on close)

### 3.2. CalculatorEngine

**Name:** Calculation Engine

**Description:** Core calculation logic that performs arithmetic and mathematical operations with precision handling and error management. Acts as the coordinator between the parser and history manager.

**Technologies:** C++, STL, CMath

**Responsibilities:**
- Basic arithmetic (+, -, *, /, %)
- Advanced functions (sqrt, sin, cos, tan, log, ln, pow)
- Power operator (^) support
- Memory storage and recall
- Result precision management
- Division by zero and overflow handling
- Result formatting with configurable precision

### 3.4. ExpressionParser

**Name:** Mathematical Expression Parser

**Description:** Parses and evaluates mathematical expressions using recursive descent parsing for operator precedence handling.

**Technologies:** C++, STL

**Responsibilities:**
- Tokenization of mathematical expressions
- Operator precedence evaluation
- Function call parsing (sin, cos, sqrt, etc.)
- Error detection for invalid expressions

### 3.5. HistoryManager

**Name:** Calculation History Manager

**Description:** Tracks and stores calculation history for review and reuse.

**Technologies:** C++, STL (QVector/QList)

**Responsibilities:**
- Store past calculations
- Limit history size (max 100 entries)
- Provide history retrieval API
- Persist history across sessions

### 3.6. DisplayWidget

**Name:** Display Widget

**Description:** Dual-line display showing current formula and calculated result using two QLineEdit fields.

**Technologies:** Qt6::Widgets

**Components:**
- `resultLabel` - Shows calculated result (36px bold font)
- `expressionLabel` - Shows current formula (14px font)

### 3.7. KeypadWidget

**Name:** Numeric Keypad Widget

**Description:** Custom button grid for numeric input and operations using QGridLayout.

**Technologies:** Qt6::Widgets, QGridLayout

**Components:**
- Numeric buttons (0-9)
- Operator buttons (+, -, *, /)
- Function buttons (sin, cos, tan, sqrt, log, ln, pow, x!)
- Memory buttons (MC, MR, MS, M+, M-)
- Clear, backspace, equals buttons
- Parentheses buttons ((), )

### 3.8. ThemeManager

**Name:** Theme Management System

**Description:** Manages application-wide theme switching between light, dark, and blue modes.

**Technologies:** Qt6::Widgets (QStyleSheet, QPalette)

**Themes:**
- Light theme (white background)
- Dark theme (#1e1e1e background)
- Blue theme (#1a2a4a background)

## 4. Data Stores

### 4.1. Calculation Buffer

**Name:** Current Calculation State

**Type:** In-memory state

**Purpose:** Stores the current expression being built by the user.

**Key Schemas:** QString-based expression storage

### 4.2. Memory Storage

**Name:** Calculator Memory

**Type:** Double-precision floating point

**Purpose:** Stores a single value for memory operations (MC, MR, M+, M-).

**Key Schemas:** double

### 4.3. History Log

**Name:** Calculation History

**Type:** Container (QList/QVector)

**Purpose:** Stores all completed calculations (formula and result).

**Key Schemas:**
- Formula: QString
- Result: double
- Timestamp: QDateTime

### 4.4. User Settings

**Name:** Application Preferences

**Type:** QSettings

**Purpose:** Persists user preferences across sessions.

**Key Schemas:**
- Theme: QString (light/dark)
- Window dimensions: QSize
- History visible: bool

## 5. External Integrations / APIs

**Service Name:** Qt6 Framework

**Purpose:** Provides GUI widgets, event handling, file I/O functionality, and cross-platform compatibility.

**Integration Method:** Library linking (Qt6::Core, Qt6::Widgets, MOC)

**Components Used:**
- `QApplication` - Application object
- `QMainWindow` - Main window container
- `QWidget` - Base widget class
- `QVBoxLayout`, `QHBoxLayout`, `QGridLayout` - Layout managers
- `QPushButton`, `QLineEdit`, `QTextEdit` - UI controls
- `QShortcut` - Keyboard shortcuts
- `QStyleSheet` - Styling
- `QSettings` - User preferences

## 6. Deployment & Infrastructure

**Build System:** CMake

**Qt Version:** Qt6 (Qt6::Core, Qt6::Widgets)

**Compiler:** C++17 compliant compiler (GCC, Clang, MSVC)

**Platform Targets:**
- Linux (Ubuntu, Fedora, Arch)
- Windows (10, 11)
- macOS (10.15+)

## 7. Security Considerations

**File Access:** No file I/O operations in core calculator logic

**Data Handling:** Calculation data stored in memory until application shutdown

**No Encryption:** Plain text display of calculations

**No Network:** Offline application

## 8. Development & Testing Environment

**Local Setup:** CMake-based build system

**Testing Framework:** Google Test (gtest)

**Code Quality Tools:** (Future)

**Build Directory:** Separate `build/` directory for out-of-source builds

## 9. Future Considerations / Roadmap

### Version 0.2.0 (COMPLETED)
- [x] Power function (x^y) - implemented ^ operator
- [x] Logarithmic functions (log10, ln)
- [x] Trigonometric functions (sin, cos, tan) with inverse functions
- [x] Square root (sqrt)
- [x] Factorial (x!)
- [x] Parentheses support for complex expressions
- [x] Scientific notation support
- [x] Degree/radian mode toggle for trig functions

### Version 0.3.0
- [ ] Implement complex number support
- [ ] Add statistical functions (mean, median, std dev)
- [ ] Implement equation solving
- [ ] Add unit conversion
- [ ] Code coverage measurement (gcov/lcov)

### Version 0.4.0
- [ ] Keyboard shortcuts for all operations (currently numbers, operators, Enter, Backspace, Escape implemented)
- [ ] Undo/redo for expression editing
- [ ] Syntax highlighting for expressions
- [ ] Search within history
- [ ] Export history to file

### Version 1.0.0
- [ ] Stable API and documentation
- [ ] Cross-platform testing
- [ ] Package distribution (deb, rpm, AppImage)
- [ ] Accessibility improvements
- [ ] Localization support

## 10. Project Identification

**Project Name:** QwenCalc

**Repository URL:** https://github.com/segin/qwencalc

**Primary Contact/Team:** segin (Kirn Gill II)

**Date of Last Update:** 2026-04-20

## 11. Glossary / Acronyms

| Term | Definition |
|------|------------|
| Qt6 | Cross-platform GUI framework used for building the application |
| CMake | Cross-platform build system generator |
| C++17 | C++ programming language standard used in the project |
| GUI | Graphical User Interface provided by Qt6 Widgets |
| MOC | Meta-Object Compiler - Qt-specific preprocessor for signal/slot mechanism |
| UI | User Interface |
| MR | Memory Recall |
| M+ | Memory Add |
| M- | Memory Subtract |
| MC | Memory Clear |
| CE | Clear Entry |
| DEL | Delete Last Character |
| QSettings | Qt class for storing user preferences |
| QString | Qt string class for Unicode text |
