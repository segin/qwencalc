#include "CalculatorWindow.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QKeyEvent>
#include <QFrame>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QShortcut>
#include <QSettings>
#include <QCloseEvent>

namespace qwencalc {

CalculatorWindow::CalculatorWindow(QWidget* parent)
    : QMainWindow(parent), historyVisible(false) {
    setupUI();
    setupConnections();
    setupShortcuts();
    loadSettings();
}

CalculatorWindow::~CalculatorWindow() {}

void CalculatorWindow::setupShortcuts() {
    // Number keys and operators from the main keyboard
    new QShortcut(QKeySequence("0"), this, this, [this]() { currentExpression += "0"; updateDisplay(); });
    new QShortcut(QKeySequence("1"), this, this, [this]() { currentExpression += "1"; updateDisplay(); });
    new QShortcut(QKeySequence("2"), this, this, [this]() { currentExpression += "2"; updateDisplay(); });
    new QShortcut(QKeySequence("3"), this, this, [this]() { currentExpression += "3"; updateDisplay(); });
    new QShortcut(QKeySequence("4"), this, this, [this]() { currentExpression += "4"; updateDisplay(); });
    new QShortcut(QKeySequence("5"), this, this, [this]() { currentExpression += "5"; updateDisplay(); });
    new QShortcut(QKeySequence("6"), this, this, [this]() { currentExpression += "6"; updateDisplay(); });
    new QShortcut(QKeySequence("7"), this, this, [this]() { currentExpression += "7"; updateDisplay(); });
    new QShortcut(QKeySequence("8"), this, this, [this]() { currentExpression += "8"; updateDisplay(); });
    new QShortcut(QKeySequence("9"), this, this, [this]() { currentExpression += "9"; updateDisplay(); });
    
    // Operators
    new QShortcut(QKeySequence("+"), this, this, [this]() { currentExpression += "+"; updateDisplay(); });
    new QShortcut(QKeySequence("-"), this, this, [this]() { currentExpression += "-"; updateDisplay(); });
    new QShortcut(QKeySequence("*"), this, this, [this]() { currentExpression += "*"; updateDisplay(); });
    new QShortcut(QKeySequence("/"), this, this, [this]() { currentExpression += "/"; updateDisplay(); });
    
    // Equals
    new QShortcut(QKeySequence("Enter"), this, this, &CalculatorWindow::onEqualsClicked);
    new QShortcut(QKeySequence("="), this, this, &CalculatorWindow::onEqualsClicked);
    
    // Backspace and Clear
    new QShortcut(QKeySequence("Backspace"), this, this, &CalculatorWindow::onBackspaceClicked);
    new QShortcut(QKeySequence("Escape"), this, this, &CalculatorWindow::onClearClicked);
    
    // Parentheses
    new QShortcut(QKeySequence("("), this, this, [this]() { currentExpression += "("; updateDisplay(); });
    new QShortcut(QKeySequence(")"), this, this, [this]() { currentExpression += ")"; updateDisplay(); });
}

void CalculatorWindow::closeEvent(QCloseEvent* event) {
    saveSettings();
    QMainWindow::closeEvent(event);
}

void CalculatorWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    display = new DisplayWidget(centralWidget);
    currentMemoryDisplay = "M = 0.00";
    memoryLabelWidget = new QLabel(currentMemoryDisplay, centralWidget);
    memoryLabelWidget->setStyleSheet("QLabel { color: #ff9800; font-weight: bold; font-size: 14px; }");
    
    QGroupBox* displayGroup = new QGroupBox("Display");
    QVBoxLayout* displayLayout = new QVBoxLayout();
    displayLayout->addWidget(display);
    displayLayout->addWidget(memoryLabelWidget);
    displayGroup->setLayout(displayLayout);
    mainLayout->addWidget(displayGroup);
    
    keypad = new KeypadWidget(centralWidget);
    
    QHBoxLayout* keypadLayout = new QHBoxLayout();
    
    keypadLayout->addWidget(keypad);
    
    historyArea = new QScrollArea();
    historyArea->setWidgetResizable(true);
    historyArea->setFixedWidth(200);
    historyArea->setVisible(false);
    
    QFrame* historyFrame = new QFrame();
    QVBoxLayout* historyLayout = new QVBoxLayout(historyFrame);
    QLabel* historyLabel = new QLabel("History");
    historyLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");
    historyLayout->addWidget(historyLabel);
    
    QTextEdit* histEdit = new QTextEdit();
    histEdit->setStyleSheet("QTextEdit { background-color: #2d2d2d; color: #d4d4d4; }");
    histEdit->setReadOnly(true);
    histEdit->setMaximumHeight(400);
    histEdit->setAcceptRichText(false);
    historyTextEdit = histEdit;
    
    historyLayout->addWidget(histEdit);
    historyArea->setWidget(historyFrame);
    keypadLayout->addWidget(historyArea);
    
    mainLayout->addLayout(keypadLayout);
    
    centralWidget->setMinimumSize(700, 550);
    setCentralWidget(centralWidget);
    setWindowTitle("QwenCalc");
    resize(700, 550);
}

void CalculatorWindow::setupConnections() {
    connect(keypad, &KeypadWidget::numberClicked, this, &CalculatorWindow::onNumberClicked);
    connect(keypad, &KeypadWidget::operatorClicked, this, &CalculatorWindow::onOperatorClicked);
    connect(keypad, &KeypadWidget::functionClicked, this, &CalculatorWindow::onFunctionClicked);
    connect(keypad, &KeypadWidget::clearClicked, this, &CalculatorWindow::onClearClicked);
    connect(keypad, &KeypadWidget::backspaceClicked, this, &CalculatorWindow::onBackspaceClicked);
    connect(keypad, &KeypadWidget::equalsClicked, this, &CalculatorWindow::onEqualsClicked);
    connect(keypad, &KeypadWidget::memoryClicked, this, [this](const QString& action) {
        if (action == "add") onMemoryAdd();
        else if (action == "subtract") onMemorySubtract();
        else if (action == "recall") onMemoryRecall();
        else if (action == "store") onMemoryStore();
        else if (action == "clear") onMemoryClear();
    });
    connect(keypad, &KeypadWidget::parenClicked, this, &CalculatorWindow::onParenClicked);
    connect(keypad, &KeypadWidget::historyToggled, this, &CalculatorWindow::onHistoryToggled);
    connect(keypad, &KeypadWidget::dotClicked, this, [this]() {
        currentExpression += ".";
        updateDisplay();
    });
}

void CalculatorWindow::applyTheme(const QString& themeName) {
    if (themeName == "dark") {
        setStyleSheet(
            "QMainWindow { background-color: #1e1e1e; }\n"
            "QGroupBox { color: white; }\n"
            "QLineEdit { background-color: #2d2d2d; color: white; padding: 5px; font-size: 16px; border: 1px solid #444; }\n"
            "QPushButton { background-color: #3a3a3a; color: white; padding: 10px; border-radius: 5px; }\n"
            "QPushButton:hover { background-color: #4a4a4a; }\n"
            "QPushButton:pressed { background-color: #2a2a2a; }\n"
            "QTextEdit { background-color: #2d2d2d; color: #d4d4d4; }\n"
            "QScrollBar:vertical { background-color: #1e1e1e; border: 1px solid #444; }\n"
            "QScrollBar::handle:vertical { background-color: #555; border-radius: 2px; }\n"
            "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 10px; }\n"
        );
    } else {
        setStyleSheet(
            "QMainWindow { background-color: white; }\n"
            "QGroupBox { color: black; }\n"
            "QLineEdit { background-color: white; color: black; padding: 5px; font-size: 16px; border: 1px solid #ccc; }\n"
            "QPushButton { background-color: #4CAF50; color: white; padding: 10px; border-radius: 5px; }\n"
            "QPushButton:hover { background-color: #45a049; }\n"
            "QPushButton:pressed { background-color: #3d8b40; }\n"
            "QTextEdit { background-color: #f5f5f5; color: black; }\n"
            "QScrollBar:vertical { background-color: white; border: 1px solid #ccc; }\n"
            "QScrollBar::handle:vertical { background-color: #ccc; border-radius: 2px; }\n"
            "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 10px; }\n"
        );
    }
}

ThemeManager& CalculatorWindow::getTheme() {
    return themeManager;
}

void CalculatorWindow::onNumberClicked(int number) {
    currentExpression += QString::number(number);
    updateDisplay();
}

void CalculatorWindow::onOperatorClicked(const QString& op) {
    currentExpression += op.toStdString();
    updateDisplay();
}

void CalculatorWindow::onFunctionClicked(const QString& func) {
    std::string funcStr = func.toStdString();
    
    if (funcStr == "sin") {
        currentExpression += "sin(";
    } else if (funcStr == "cos") {
        currentExpression += "cos(";
    } else if (funcStr == "tan") {
        currentExpression += "tan(";
    } else if (funcStr == "log") {
        currentExpression += "log(";
    } else if (funcStr == "ln") {
        currentExpression += "ln(";
    } else if (funcStr == "sqrt") {
        currentExpression += "sqrt(";
    } else if (funcStr == "x^y") {
        currentExpression += "^";
    } else if (funcStr == "x!") {
        currentExpression += "!";
    }
    
    updateDisplay();
}

   void CalculatorWindow::onClearClicked() {
    currentExpression.clear();
    display->clearDisplay();
}

void CalculatorWindow::onParenClicked(const QString& paren) {
    if (paren == "(") {
        currentExpression += "(";
    } else if (paren == ")") {
        currentExpression += ")";
    }
    updateDisplay();
}

void CalculatorWindow::onBackspaceClicked() {
    if (!currentExpression.isEmpty()) {
        currentExpression.removeLast();
        display->displayResult(QString::fromUtf8(currentExpression.toStdString().c_str()));
    }
}

    void CalculatorWindow::onEqualsClicked() {
    double result;
    try {
        result = engine.calculate(currentExpression.toStdString());
    } catch (const std::exception& e) {
        display->displayResult("Error: " + QString::fromStdString(e.what()));
        return;
    }
    
    std::string resultStr = engine.formatResult(result);
    QString displayResult(QString::fromStdString(resultStr));
    display->displayResult(displayResult);
    
    updateHistory();
    
    currentExpression.clear();
}

void CalculatorWindow::onMemoryAdd() {
    try {
        double result = 0.0;
        if (!currentExpression.isEmpty()) {
            result = engine.calculate(currentExpression.toStdString());
        } else {
            result = engine.calculate(engine.getLastResult().c_str());
        }
        engine.addToMemory(result);
        currentMemoryDisplay = QString("M = %1").arg(engine.getMemory(), 0, 'f', 2);
        memoryLabelWidget->setText(currentMemoryDisplay);
        display->displayResult(currentMemoryDisplay);
    } catch (...) {
        display->displayResult("Memory Error");
    }
}

void CalculatorWindow::onMemorySubtract() {
    try {
        double result = 0.0;
        if (!currentExpression.isEmpty()) {
            result = engine.calculate(currentExpression.toStdString());
        } else {
            result = engine.calculate(engine.getLastResult().c_str());
        }
        engine.subtractFromMemory(result);
        currentMemoryDisplay = QString("M = %1").arg(engine.getMemory(), 0, 'f', 2);
        memoryLabelWidget->setText(currentMemoryDisplay);
        display->displayResult(currentMemoryDisplay);
    } catch (...) {
        display->displayResult("Memory Error");
    }
}

void CalculatorWindow::onMemoryStore() {
    try {
        double result = 0.0;
        if (!currentExpression.isEmpty()) {
            result = engine.calculate(currentExpression.toStdString());
            engine.storeMemory(currentExpression.toStdString());
            currentExpression.clear();
            currentMemoryDisplay = QString("M = %1").arg(result, 0, 'f', 2);
        } else {
            engine.storeMemory("0");
            currentMemoryDisplay = "M = 0.00";
        }
        memoryLabelWidget->setText(currentMemoryDisplay);
        display->displayResult(currentMemoryDisplay);
    } catch (...) {
        display->displayResult("Store Error");
    }
}

void CalculatorWindow::onMemoryRecall() {
    try {
        double mem = engine.getMemory();
        QString memStr = QString::number(mem, 'g', 10);
        currentExpression = memStr;
        updateDisplay();
    } catch (...) {
        display->displayResult("Recall Error");
    }
}

void CalculatorWindow::onMemoryClear() {
    try {
        engine.setMemory(0.0);
        currentMemoryDisplay = "M = 0.00";
        memoryLabelWidget->setText(currentMemoryDisplay);
        display->displayResult(currentMemoryDisplay);
    } catch (...) {
        display->displayResult("Memory Error");
    }
}

void CalculatorWindow::onHistoryToggled() {
    historyVisible = !historyVisible;
    historyArea->setVisible(historyVisible);
    if (historyVisible) updateHistory();
}

void CalculatorWindow::onThemeChanged() {
    static bool dark = false;
    dark = !dark;
    applyTheme(dark ? "dark" : "light");
}

 void CalculatorWindow::updateDisplay() {
    display->displayResult(currentExpression);
}

void CalculatorWindow::updateHistory() {
    QString formattedHistory;
    std::string history = engine.getHistory();
    
    size_t start = 0;
    size_t pos = 0;
    
    while ((pos = history.find('\n', start)) != std::string::npos) {
        std::string line = history.substr(start, pos - start);
        start = pos + 1;
        
        if (line.empty()) continue;
        
        size_t equalPos = line.find('=');
        if (equalPos > 0) {
            QString expression = QString::fromStdString(line.substr(0, equalPos));
            QString result = QString::fromStdString(line.substr(equalPos + 1));
            formattedHistory += QString("<div style='color: #d4d4d4; margin: 2px;'>%1 = <span style='color: #4CAF50;'>%2</span></div>")
                                .arg(expression).arg(result);
        }
    }
    
    if (formattedHistory.isEmpty()) {
        formattedHistory = "<div style='color: #888;'>No history yet</div>";
    }
    
    historyTextEdit->setText(formattedHistory);
    historyTextEdit->setMaximumHeight(400);
}

void CalculatorWindow::loadSettings() {
    QSettings settings("QwenCalc", "Calculator");
    QString theme = settings.value("theme", "light").toString();
    applyTheme(theme);
    
    int width = settings.value("windowWidth", 700).toInt();
    int height = settings.value("windowHeight", 550).toInt();
    resize(width, height);
    
    historyVisible = settings.value("historyVisible", false).toBool();
    historyArea->setVisible(historyVisible);
}

void CalculatorWindow::saveSettings() {
    QSettings settings("QwenCalc", "Calculator");
    settings.setValue("windowWidth", width());
    settings.setValue("windowHeight", height());
    settings.setValue("historyVisible", historyVisible);
}

} // namespace qwencalc
