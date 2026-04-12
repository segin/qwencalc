# ARCHITECTURE.md

## 1. Project Structure

```
[Project Root]/
├── src/              # Main source code
│   └── App/          # Application module
│       └── src/      # Application source files
│           ├── main.cpp
│           ├── calculatorapp.cpp
│           └── calculatorapp.h
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

### 3.1. CalculatorApp

**Name:** Calculator Application

**Description:** A desktop calculator application providing a graphical user interface for mathematical calculations. The main window contains a display area showing formula and results, a numeric keypad, and a history panel for reviewing past calculations.

**Technologies:** C++ (Qt6), Widgets, Core

**Deployment:** Local desktop application

**Responsibilities:**
- Window management and layout
- User input handling (mouse and keyboard)
- Theme switching (light/dark modes)
- History panel display and interaction
- Menu and toolbar operations

### 3.2. calculatorapp.h/cpp

**Name:** Main Application Logic

**Description:** Contains the core calculator window implementation, UI component management, signal/slot connections, and application state handling.

**Technologies:** Qt6::Widgets, Qt6::Core, C++17, Signals/Slots

**Deployment:** N/A (part of application)

**Key Methods:**
- `setupUI()` - Initialize all UI components
- `setupConnections()` - Connect signals and slots
- `onEqualsClicked()` - Trigger calculation
- `onMemoryAdd()` / `onMemorySubtract()` - Memory operations
- `onHistoryToggled()` - Show/hide history panel

### 3.3. CalculatorEngine

**Name:** Calculation Engine

**Description:** Core calculation logic that performs arithmetic and mathematical operations with precision handling and error management.

**Technologies:** C++, STL, CMath

**Responsibilities:**
- Basic arithmetic (+, -, *, /, %)
- Advanced functions (sqrt, sin, cos, tan, log, power)
- Memory storage and recall
- Result precision management
- Division by zero and overflow handling

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

**Description:** Dual-line display showing current formula and calculated result.

**Technologies:** Qt6::Widgets

**Components:**
- `resultLabel` - Shows calculated result
- `expressionLabel` - Shows current formula

### 3.7. KeypadWidget

**Name:** Numeric Keypad Widget

**Description:** Custom button grid for numeric input and operations.

**Technologies:** Qt6::Widgets, QGridLayout

**Components:**
- Numeric buttons (0-9)
- Operator buttons (+, -, *, /)
- Function buttons (sin, cos, tan, sqrt, log)
- Memory buttons (MC, MR, M+, M-)
- Clear, backspace, equals buttons

### 3.8. ThemeManager

**Name:** Theme Management System

**Description:** Manages application-wide theme switching between light and dark modes.

**Technologies:** Qt6::Widgets (QStyleSheet)

**Themes:**
- Light theme (white background)
- Dark theme (#1e1e1e background)

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

### Version 0.2.0
- [ ] Add scientific notation for very large/small numbers
- [ ] Implement degree/radian mode toggle for trig functions
- [ ] Add parentheses support for complex expressions
- [ ] Implement power function (x^y)
- [ ] Add logarithmic functions (log10, ln)

### Version 0.3.0
- [ ] Implement complex number support
- [ ] Add statistical functions (mean, median, std dev)
- [ ] Implement equation solving
- [ ] Add unit conversion

### Version 1.0.0
- [ ] Add syntax highlighting for expressions
- [ ] Implement search within history
- [ ] Add export history to file
- [ ] Add undo/redo for expression editing
- [ ] Add customizable keyboard shortcuts

## 10. Project Identification

**Project Name:** QwenCalc

**Repository URL:** https://github.com/segin/qwencalc

**Primary Contact/Team:** segin (Kirn Gill II)

**Date of Last Update:** 2026-04-10

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
