# QwenCalc Requirements Document (INCOSE/EARS Format)

## 1. Introduction

### 1.1 Purpose
This document defines the functional and non-functional requirements for QwenCalc, a desktop calculator application built with C++ and Qt6.

### 1.2 Scope
QwenCalc provides a modern, intuitive calculator interface with basic arithmetic, advanced mathematical operations, memory functions, and history tracking.

### 1.3 Definitions and Acronyms
- **UI**: User Interface
- **GUI**: Graphical User Interface
- **MD**: Mathematical Display
- **MC**: Memory Clear
- **MR**: Memory Recall
- **M+**: Memory Add
- **M-**: Memory Subtract
- **CE**: Clear Entry
- **C**: Clear All
- **DEL**: Delete Last Character

### 1.4 Overall Description
QwenCalc is a desktop calculator application for Windows, macOS, and Linux. It features a Qt6-based GUI with support for keyboard shortcuts, customizable themes (light/dark), and calculation history.

---

## 2. Overall Requirements

### 2.1 Functional Requirements

#### FR-01: Basic Arithmetic Operations
**ID**: FR-01
**Priority**: High
**ReqID**: REQ-001
**Name**: Basic Arithmetic Calculator

**Description**: The system shall perform basic arithmetic operations.

**Stimulus**: User inputs numbers and operators via keyboard or GUI buttons.

**Response**: The system shall display the calculated result.

**Acceptance Criteria**:
- Addition (+): Correctly calculates sums
- Subtraction (-): Correctly calculates differences
- Multiplication (*): Correctly calculates products
- Division (/): Correctly calculates quotients (with division by zero handling)

**Rationale**: Essential calculator functionality.

---

#### FR-02: Advanced Mathematical Operations
**ID**: FR-02
**Priority**: Medium
**ReqID**: REQ-002
**Name**: Advanced Math Functions

**Description**: The system shall perform advanced mathematical operations.

**Response**: The system shall calculate and display results for:
- Square root (√)
- Powers (x^y, x²)
- Trigonometric functions (sin, cos, tan)
- Logarithms (log, ln)
- Absolute value (|x|)

**Acceptance Criteria**:
- Square root of non-negative numbers returns correct result
- Powers calculation handles integer and fractional exponents
- Trigonometric functions support degree/radian modes
- Logarithms handle valid domain (positive numbers for log)

**Rationale**: Extends calculator functionality for scientific use.

---

#### FR-03: Memory Functions
**ID**: FR-03
**Priority**: Medium
**ReqID**: REQ-003
**Name**: Memory Operations

**Description**: The system shall provide memory storage and retrieval functions.

**Response**: The system shall support:
- **MC**: Clear memory
- **MR**: Recall memory to display
- **M+**: Add current value to memory
- **M-**: Subtract current value from memory

**Acceptance Criteria**:
- Memory persists across calculation sessions within application lifetime
- Display shows memory indicator when value stored
- MR displays memory value
- M+ adds to existing memory or initializes with current value
- M- subtracts from existing memory

**Rationale**: Enables multi-step calculations with intermediate values.

---

#### FR-04: Display and Input
**ID**: FR-04
**Priority**: High
**ReqID**: REQ-004
**Name**: Display and Input Management

**Description**: The system shall provide a dual-line display and flexible input methods.

**Response**: The system shall:
- Display current formula in upper line
- Display intermediate result in lower line
- Accept input via on-screen buttons and keyboard
- Support keyboard shortcuts for all operations

**Acceptance Criteria**:
- Formula line shows complete expression being built
- Result line shows current calculated value
- Keyboard input mirrors button functionality
- Common shortcuts: Enter=calculate, Esc=clear, Backspace=delete, etc.

**Rationale**: Standard calculator UX pattern.

---

#### FR-05: Clear and Delete Operations
**ID**: FR-05
**Priority**: High
**ReqID**: REQ-005
**Name**: Clear Operations

**Description**: The system shall provide clear and delete functionality.

**Response**: The system shall:
- **CE**: Clear entry (clear current number being entered)
- **C**: Clear all (reset entire calculation)
- **DEL**: Delete last character from formula

**Acceptance Criteria**:
- CE affects only current number input
- C resets entire state to initial condition
- DEL removes last character from formula line

**Rationale**: Essential error correction and state management.

---

#### FR-06: History Tracking
**ID**: FR-06
**Priority**: Medium
**ReqID**: REQ-006
**Name**: Calculation History

**Description**: The system shall track and display calculation history.

**Response**: The system shall:
- Store all completed calculations
- Display history in a sidebar or popup
- Allow users to click history entries to reuse them
- Limit history size (e.g., 100 entries)

**Acceptance Criteria**:
- History shows formula and result for each calculation
- History entries are clickable to restore as current formula
- History persists across application sessions
- Maximum 100 entries maintained

**Rationale**: Enables review and reuse of past calculations.

---

#### FR-07: Theme Customization
**ID**: FR-07
**Priority**: Low
**ReqID**: REQ-007
**Name**: Theme Management

**Description**: The system shall support theme switching.

**Response**: The system shall:
- Provide light theme (default)
- Provide dark theme
- Allow theme switching via menu or shortcut

**Acceptance Criteria**:
- Theme affects colors of all UI elements
- Theme selection persists across sessions
- Theme switch takes effect immediately

**Rationale**: User preference and accessibility.

---

### 2.2 Non-Functional Requirements

#### NFR-01: Performance
**ID**: NFR-01
**Priority**: High
**ReqID**: REQ-101
**Name**: Calculation Performance

**Description**: Calculations shall be performed with minimal latency.

**Response Time**: < 50ms for any calculation operation.

**Acceptance Criteria**:
- All arithmetic operations complete in < 1ms
- Complex expressions complete in < 50ms
- No UI freezing during calculation

**Rationale**: User experience requirement.

---

#### NFR-02: Precision
**ID**: NFR-02
**Priority**: High
**ReqID**: REQ-102
**Name**: Numerical Precision

**Description**: Calculations shall maintain appropriate precision.

**Response**: The system shall:
- Support floating-point numbers
- Display up to 15 significant digits
- Round display to 10 decimal places for readability

**Acceptance Criteria**:
- No precision loss within standard floating-point range
- Scientific notation for very large/small numbers
- Proper rounding for display

**Rationale**: Accuracy requirement for calculator.

---

#### NFR-03: Cross-Platform Support
**ID**: NFR-03
**Priority**: Medium
**ReqID**: REQ-103
**Name**: Platform Compatibility

**Description**: The system shall run on multiple platforms.

**Platforms**:
- Linux (Ubuntu, Fedora, Arch, etc.)
- Windows (10, 11)
- macOS (10.15+)

**Acceptance Criteria**:
- Consistent UI across platforms
- Same functionality on all platforms
- Platform-specific shortcuts where appropriate

**Rationale**: Broad user base.

---

#### NFR-04: Error Handling
**ID**: NFR-04
**Priority**: High
**ReqID**: REQ-104
**Name**: Error Handling

**Description**: The system shall handle invalid inputs gracefully.

**Response**: The system shall display appropriate error messages for:
- Division by zero
- Invalid mathematical operations
- Overflow conditions

**Acceptance Criteria**:
- Division by zero shows "Error" or "Undefined"
- Invalid operations (e.g., √(-1) in real mode) handled appropriately
- No application crashes on invalid input

**Rationale**: Robustness requirement.

---

#### NFR-05: Reliability
**ID**: NFR-05
**Priority**: Medium
**ReqID**: REQ-105
**Name**: Application Reliability

**Description**: The system shall maintain stability during extended use.

**Acceptance Criteria**:
- No memory leaks over extended use
- History survives application restart
- No crashes during normal operation

**Rationale**: User trust requirement.

---

## 3. User Stories

### US-01: Basic Calculator
**As a** calculator user
**I want** to perform basic arithmetic operations
**So that** I can calculate sums, differences, products, and quotients

**Acceptance Criteria**:
- Given I enter numbers and operators, I see the correct result
- Given I divide by zero, I see an error message

---

### US-02: Advanced Functions
**As a** student or professional
**I want** to perform advanced mathematical calculations
**So that** I can solve complex mathematical problems

**Acceptance Criteria**:
- Given I select sqrt, cos, sin, tan, or log, I can enter the value
- Given I enter a valid operation, I see the correct result

---

### US-03: Memory Storage
**As a** multi-step calculator user
**I want** to store values in memory
**So that** I can use them across multiple calculations

**Acceptance Criteria**:
- Given I use M+, I can recall the value using MR
- Given I use M-, I can subtract from stored value

---

### US-04: Calculation Review
**As a** user who needs to review past calculations
**I want** to see calculation history
**So that** I can reference or reuse previous results

**Acceptance Criteria**:
- Given I complete a calculation, it appears in history
- Given I click a history entry, I can reuse it

---

### US-05: Visual Comfort
**As a** user who works long hours
**I want** to switch between light and dark themes
**So that** I can reduce eye strain

**Acceptance Criteria**:
- Given I switch themes, all UI elements update
- Given I restart the app, my theme preference is restored

---

### US-06: Keyboard Efficiency
**As a** power user
**I want** to use keyboard shortcuts
**So that** I can operate quickly without using the mouse

**Acceptance Criteria**:
- Given I press Enter, I get the result
- Given I press Esc, I clear the display
- Given I press Backspace, I delete one character

---

## 4. Traceability

### 4.1 Requirements to Features

| ReqID | Feature |
|-------|---------|
| REQ-001 | Basic Arithmetic |
| REQ-002 | Advanced Math Functions |
| REQ-003 | Memory Operations |
| REQ-004 | Display and Input |
| REQ-005 | Clear Operations |
| REQ-006 | Calculation History |
| REQ-007 | Theme Management |

### 4.2 User Stories to Requirements

| Story ID | Requirement |
|----------|-------------|
| US-01 | REQ-001 |
| US-02 | REQ-002 |
| US-03 | REQ-003 |
| US-04 | REQ-006 |
| US-05 | REQ-007 |
| US-06 | REQ-004, REQ-005 |

---

## 5. Appendix

### 5.1 Keyboard Shortcuts

| Key | Action |
|-----|--------|
| 0-9 | Enter digits |
| + | Addition |
| - | Subtraction |
| * | Multiplication |
| / | Division |
| Enter | Calculate |
| Esc | Clear All |
| Backspace | Delete Character |
| . | Decimal Point |
| ( | Open Parenthesis |
| ) | Close Parenthesis |

### 5.2 Display Format

- Formula line: Shows complete expression (e.g., "12 + 5 * 3")
- Result line: Shows current calculated value (e.g., "27")

---

## Document Control

- **Version**: 1.0
- **Date**: 2026-04-10
- **Author**: QwenCalc Development Team
- **Status**: Draft
