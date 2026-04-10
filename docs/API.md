# QwenCalc API Documentation

## Backend API

### ExpressionParser

Core mathematical expression parsing component.

```cpp
class ExpressionParser {
public:
    ExpressionParser();
    double parse(const std::string& expression);
    
    // Mathematical operations
    double factorial(int n) const;
    double factorial(double n) const;
    
    // Utility functions
    bool isOperatorChar(char c) const;
    bool isFunctionChar(char c) const;
    bool isWhitespace(char c) const;
};
```

**Supported Operations:**
- Arithmetic: `+`, `-`, `*`, `/`, `%`
- Trigonometric: `sin()`, `cos()`, `tan()`
- Logarithmic: `log()`, `ln()`
- Other: `sqrt()`, `pow()`, `factorial()`

### CalculatorEngine

Main calculator engine with calculation logic.

```cpp
class CalculatorEngine {
public:
    CalculatorEngine();
    
    // Core functionality
    double calculate(const std::string& expression);
    
    // Memory functions
    double getMemory() const;
    void setMemory(double memory);
    void addToMemory(double value);
    void subtractFromMemory(double value);
    void recallMemory();
    void storeMemory(const std::string& expression);
    
    // History
    std::string getHistory() const;
    std::string getLastResult() const;
    std::string getLastExpression() const;
    
    // Configuration
    void setPrecision(int precision);
    int getPrecision() const;
};
```

### HistoryManager

Tracks calculation history.

```cpp
class HistoryManager {
public:
    HistoryManager();
    void addEntry(const std::string& expression, double result);
    std::string getHistory() const;
    int size() const;
    void clear();
};
```

## Frontend API

### CalculatorWindow

Main application window.

```cpp
class CalculatorWindow : public QMainWindow {
public:
    explicit CalculatorWindow(QWidget* parent = nullptr);
    
    void applyTheme(const QString& themeName);
    void clearHistory();
    void updateDisplay();
};
```

### DisplayWidget

Displays calculation results.

```cpp
class DisplayWidget : public QWidget {
public:
    void displayResult(const QString& result);
    void displayExpression(const QString& expression);
    void clearDisplay();
};
```

### KeypadWidget

Numeric keypad with function buttons.

```cpp
class KeypadWidget : public QWidget {
public:
    void addButton(const QString& text, const QString& type);
    void setupKeypad();
};
```

## Signals and Slots

### KeypadWidget Signals

- `numberClicked(int number)`
- `operatorClicked(const QString& op)`
- `functionClicked(const QString& func)`
- `clearClicked()`
- `equalsClicked()`
- `backspaceClicked()`
- `memoryClicked(const QString& action)`

### CalculatorWindow Slots

- `onNumberClicked()`
- `onOperatorClicked()`
- `onFunctionClicked()`
- `onClearClicked()`
- `onEqualsClicked()`
- `onMemoryAdd()`
- `onMemorySubtract()`
- `onMemoryRecall()`
- `onMemoryStore()`

## Error Handling

All calculation errors throw `ExpressionError`:

- `Division by zero`
- `Modulo by zero`
- `Empty expression`
- `Invalid operator`
- `Factorial overflow`
- `Unexpected character`

## Example Usage

```cpp
#include "CalculatorEngine.h"

int main() {
    CalculatorEngine engine;
    
    double result = engine.calculate("2 + 3 * 4");
    qDebug() << "Result:" << result;  // 14
    
    engine.calculate("sin(90)");
    double memory = engine.getMemory();
    
    engine.addToMemory(5);
    double recall = engine.getMemory();
    
    return 0;
}
```

## Build Requirements

```cpp
#include <QApplication>
#include <QMainWindow>
#include "CalculatorWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    CalculatorWindow window;
    window.show();
    return app.exec();
}
```
