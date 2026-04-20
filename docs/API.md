# QwenCalc API Documentation

## Backend API

### ExpressionParser

Core mathematical expression parsing component.

```cpp
class ExpressionParser {
public:
    ExpressionParser();
    double parse(const std::string& expression);

private:
    double parseExpression(int& pos) const;
    double parseTerm(int& pos) const;
    double parseFactor(int& pos) const;
    double parseNumber(int& pos) const;
    double applyUnaryOperator(char op, double value) const;
    void skipWhitespace(int& pos) const;
};
```

**Exception:**
- `ExpressionError` — extends `std::runtime_error`, thrown for invalid expressions

**Supported Operations:**
- Arithmetic: `+`, `-`, `*`, `/`
- Trigonometric: `sin()`, `cos()`, `tan()`
- Logarithmic: `log()`, `ln()`
- Other: `sqrt()`, `pow()`, factorial `!`
- Scientific notation support via `parseNumber()`

### CalculatorEngine

Main calculator engine with calculation logic.

```cpp
class CalculatorEngine {
public:
    CalculatorEngine();

    double calculate(const std::string& expression);

    void clear();
    void clearHistory();

    double getMemory() const;
    void setMemory(double memory);

    void addToMemory(double value);
    void subtractFromMemory(double value);
    void recallMemory();
    void storeMemory(const std::string& expression);

    std::string getHistory() const;
    std::string getLastResult() const;
    std::string getLastExpression() const;

    std::string formatResult(double value);

    void setPrecision(int precision);
    int getPrecision() const;

    bool isValidExpression(const std::string& expression);

private:
    double applyRounding(double value);
};
```

### HistoryManager

Tracks calculation history with file persistence.

```cpp
class HistoryManager {
public:
    HistoryManager();

    void addEntry(const std::string& expression, double result);

    void clear();

    int size() const;

    std::string getHistory() const;
    std::vector<std::string> getHistoryList() const;

    double getLastResult() const;
    std::string getLastEntry() const;

    void setMaxEntries(int maxEntries);
    int getMaxEntries() const;

    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
};
```

**Data Structure:**

```cpp
struct HistoryEntry {
    std::string expression;
    double result;
    time_t timestamp;
};
```

## Frontend API

### ThemeManager

Manages application themes and color schemes.

```cpp
class ThemeManager {
public:
    ThemeManager();

    void loadTheme(const QString& themeName);
    void saveTheme(const QString& themeName);
    void deleteTheme(const QString& themeName);
    void listThemes();

    QColor getBackgroundColor() const;
    QColor getTextColor() const;
    QColor getButtonColor() const;
    QColor getButtonHoverColor() const;
    QColor getButtonPressedColor() const;
    QColor getDisplayBackground() const;
    QColor getDisplayText() const;

    void setBackgroundColor(const QColor& color);
    void setTextColor(const QColor& color);
    void setButtonColor(const QColor& color);
    void setButtonHoverColor(const QColor& color);
    void setButtonPressedColor(const QColor& color);
    void setDisplayBackground(const QColor& color);
    void setDisplayText(const QColor& color);

    void applyThemeToWidget(QWidget* widget);

    QString getCurrentTheme() const;
    QList<QString> getAvailableThemes() const;
};
```

### CalculatorWindow

Main application window.

```cpp
class CalculatorWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit CalculatorWindow(QWidget* parent = nullptr);
    ~CalculatorWindow() override;

    void applyTheme(const QString& themeName);
    ThemeManager& getTheme();

private slots:
    void onNumberClicked(int number);
    void onOperatorClicked(const QString& op);
    void onFunctionClicked(const QString& func);
    void onClearClicked();
    void onBackspaceClicked();
    void onEqualsClicked();
    void onMemoryAdd();
    void onMemorySubtract();
    void onMemoryRecall();
    void onMemoryStore();
    void onMemoryClear();
    void onParenClicked(const QString& paren);
    void onHistoryToggled();
    void onThemeChanged();

private:
    void setupUI();
    void setupConnections();
    void setupShortcuts();
    void updateDisplay();
    void updateHistory();
    void loadSettings();
    void saveSettings();
    void closeEvent(QCloseEvent* event) override;
};
```

### DisplayWidget

Displays calculation results and expressions.

```cpp
class DisplayWidget : public QWidget {
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget* parent = nullptr);

    void displayResult(const QString& result);
    void displayExpression(const QString& expression);
    void clearDisplay();

    void setTheme(const QString& themeName);
    void setTextColor(const QColor& color);
    void setBackgroundColor(const QColor& color);

    QString getResult() const;
    QString getExpression() const;

private slots:
    void onTextChanged();

private:
    QLineEdit* resultLabel;
    QLineEdit* expressionLabel;

    QFont resultFont;
    QFont expressionFont;
};
```

### KeypadWidget

Numeric keypad with function buttons.

```cpp
class KeypadWidget : public QWidget {
    Q_OBJECT

public:
    explicit KeypadWidget(QWidget* parent = nullptr);

    QPushButton* addButton(const QString& text, const QString& type, const QColor& color);
    void setupKeypad();

    void setTheme(const QString& themeName);
    void setButtonColor(const QColor& color);
    void setTextColor(const QColor& color);

    void setButtonsEnabled(bool enabled);
    void setButtonsDisabled(bool disabled);

signals:
    void numberClicked(int number);
    void operatorClicked(const QString& op);
    void functionClicked(const QString& func);
    void clearClicked();
    void equalsClicked();
    void backspaceClicked();
    void memoryClicked(const QString& action);
    void historyToggled();
    void dotClicked();
    void parenClicked(const QString& paren);

private slots:
    void onButtonClick();
};
```

## Signals and Slots

### KeypadWidget Signals

- `numberClicked(int number)` — emitted when a number button is clicked
- `operatorClicked(const QString& op)` — emitted when an operator is clicked
- `functionClicked(const QString& func)` — emitted when a function button is clicked
- `clearClicked()` — emitted when the clear button is clicked
- `equalsClicked()` — emitted when the equals button is clicked
- `backspaceClicked()` — emitted when the backspace button is clicked
- `memoryClicked(const QString& action)` — emitted when a memory action is clicked (e.g., "MC", "M+", "M-", "MR")
- `historyToggled()` — emitted when the history toggle button is clicked
- `dotClicked()` — emitted when the decimal point button is clicked
- `parenClicked(const QString& paren)` — emitted when a parenthesis button is clicked

### CalculatorWindow Slots

- `onNumberClicked(int number)`
- `onOperatorClicked(const QString& op)`
- `onFunctionClicked(const QString& func)`
- `onClearClicked()`
- `onBackspaceClicked()`
- `onEqualsClicked()`
- `onMemoryAdd()`
- `onMemorySubtract()`
- `onMemoryRecall()`
- `onMemoryStore()`
- `onMemoryClear()`
- `onParenClicked(const QString& paren)`
- `onHistoryToggled()`
- `onThemeChanged()`

## Error Handling

All calculation errors throw `ExpressionError`:

- `Division by zero`
- `Modulo by zero`
- `Empty expression`
- `Invalid operator`
- `Unexpected character`

## Example Usage

```cpp
#include "CalculatorEngine.h"
#include "HistoryManager.h"

int main() {
    CalculatorEngine engine;

    double result = engine.calculate("2 + 3 * 4");
    engine.calculate("sin(90)");
    engine.calculate("sqrt(16)");

    engine.setMemory(42.0);
    double memory = engine.getMemory();

    engine.addToMemory(5);
    engine.subtractFromMemory(2);
    engine.recallMemory();
    engine.storeMemory("last calculation");

    std::cout << engine.getHistory() << std::endl;
    std::cout << engine.getLastResult() << std::endl;
    std::cout << engine.getLastExpression() << std::endl;

    bool valid = engine.isValidExpression("2 + 2");

    engine.setPrecision(10);
    std::string formatted = engine.formatResult(3.14159265);

    engine.clear();
    engine.clearHistory();

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

All components reside in the `qwencalc` namespace.

```cpp
#include "CalculatorEngine.h"
#include "ExpressionParser.h"
#include "HistoryManager.h"
#include "DisplayWidget.h"
#include "KeypadWidget.h"
#include "CalculatorWindow.h"
#include "ThemeManager.h"

using namespace qwencalc;
```
