# QwenCalc Project Plan

## Overview
A desktop calculator tool built with C++ and Qt, featuring a modern UI and robust backend calculation engine.

## Project Structure
```
qwencalc/
├── CMakeLists.txt           # Main CMake configuration
├── backend/                 # Core calculation logic
│   ├── CalculatorEngine.h   # Main calculation engine
│   ├── CalculatorEngine.cpp # Implementation
│   ├── ExpressionParser.h   # Mathematical expression parser
│   ├── ExpressionParser.cpp # Parser implementation
│   ├── HistoryManager.h     # Calculation history tracking
│   └── HistoryManager.cpp   # History implementation
├── frontend/                # Qt-based user interface
│   ├── CalculatorWindow.h   # Main calculator window
│   ├── CalculatorWindow.cpp # Window implementation
│   ├── DisplayWidget.h      # Display with formula/result
│   ├── DisplayWidget.cpp    # Display implementation
│   ├── KeypadWidget.h       # Numeric keypad
│   ├── KeypadWidget.cpp     # Keypad implementation
│   └── ThemeManager.h       # Theme/color management
    └── ThemeManager.cpp     # Theme implementation
├── src/                     # Main application entry
│   └── main.cpp             # Application initialization
├── tests/                   # Unit and integration tests
│   ├── CMakeLists.txt       # Test build configuration
│   ├── test_CalculatorEngine.cpp
│   ├── test_ExpressionParser.cpp
│   ├── test_HistoryManager.cpp
│   ├── test_frontend.cpp
│   └── test_integration.cpp
├── docs/                    # Documentation
│   └── API.md               # API documentation
└── README.md                # Project overview
```

## Subagents

### 1. Backend Logic Agent (`backend/`)
**Tasklist:**
- [ ] `backend/CalculatorEngine.h` - Define interface
- [ ] `backend/CalculatorEngine.cpp` - Implement core logic
- [ ] `backend/ExpressionParser.h` - Define parser interface
- [ ] `backend/ExpressionParser.cpp` - Implement recursive descent parser
- [ ] `backend/HistoryManager.h` - Define history interface
- [ ] `backend/HistoryManager.cpp` - Implement history tracking
- [ ] Unit tests for all backend components

### 2. Frontend UI Agent (`frontend/`)
**Tasklist:**
- [ ] `frontend/DisplayWidget.h` - Define display interface
- [ ] `frontend/DisplayWidget.cpp` - Implement formula/result display
- [ ] `frontend/KeypadWidget.h` - Define keypad interface
- [ ] `frontend/KeypadWidget.cpp` - Implement button layout
- [ ] `frontend/CalculatorWindow.h` - Define main window interface
- [ ] `frontend/CalculatorWindow.cpp` - Implement main window logic
- [ ] `frontend/ThemeManager.h` - Define theme interface
- [ ] `frontend/ThemeManager.cpp` - Implement theme switching
- [ ] Keyboard shortcut integration
- [ ] UI unit tests

### 3. Testing Agent (`tests/`)
**Tasklist:**
- [ ] `tests/CMakeLists.txt` - Configure test build
- [ ] `tests/test_CalculatorEngine.cpp` - Engine unit tests
- [ ] `tests/test_ExpressionParser.cpp` - Parser unit tests
- [ ] `tests/test_HistoryManager.cpp` - History unit tests
- [ ] `tests/test_frontend.cpp` - UI widget tests
- [ ] `tests/test_integration.cpp` - Integration tests
- [ ] CI/CD pipeline setup

### 4. Build & Deployment Agent
**Tasklist:**
- [ ] `CMakeLists.txt` - Configure Qt6 build system
- [ ] `src/main.cpp` - Application entry point
- [ ] `build.sh` - Build script
- [ ] `.github/workflows/ci.yml` - CI/CD pipeline
- [ ] Cross-platform build verification

## Milestones (Overall)

### Phase 1: Backend Foundation (Complete)
- [x] ExpressionParser implemented and tested
- [x] CalculatorEngine implemented and tested
- [x] HistoryManager implemented and tested

### Phase 2: Frontend Implementation (Complete)
- [x] DisplayWidget implemented
- [x] KeypadWidget implemented
- [x] CalculatorWindow implemented
- [x] ThemeManager implemented

### Phase 3: Integration (In Progress)
- [x] Main application entry point (`src/main.cpp`)
- [x] Backend + Frontend integration code complete
- [ ] Build and test on Linux
- [ ] Keyboard shortcuts working
- [ ] End-to-end testing

### Phase 4: Testing & Release (Pending)
- [ ] All unit tests passing
- [ ] Integration tests complete
- [ ] CI/CD pipeline working
- [ ] Documentation complete
- [ ] Initial release

## Testing Strategy

### Unit Tests
- Mock-based testing for backend components
- Property-based tests for calculation accuracy
- Edge case testing (zero division, overflow, etc.)

### UI Tests
- Widget interaction tests
- Layout validation tests
- Theme switching tests

### Integration Tests
- End-to-end calculation flows
- Memory function verification
- History tracking verification

## CI/CD Pipeline

### Build Pipeline
- Linux (Qt6, GCC)
- Windows (Qt6, MSVC)
- macOS (Qt6, Clang)

### Testing Pipeline
- All unit tests on every commit
- Integration tests on pull requests
- Coverage reporting

## Release Strategy

### Version 0.1.0
- Basic calculator functionality
- Light and dark themes
- History tracking

### Version 0.2.0
- Advanced mathematical functions
- Improved expression parsing
- Keyboard shortcuts

### Version 1.0.0
- Full feature set
- Complete documentation
- Polished UI/UX
