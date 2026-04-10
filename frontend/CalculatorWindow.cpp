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
#include <QShortcut>
#include <QMessageBox>
#include <QFrame>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

namespace qwencalc {

CalculatorWindow::CalculatorWindow(QWidget* parent)
    : QMainWindow(parent), historyVisible(false) {
    setupUI();
    setupConnections();
}

CalculatorWindow::~CalculatorWindow() {}

void CalculatorWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    display = new DisplayWidget(centralWidget);
    expressionLine = new QLineEdit(centralWidget);
    expressionLine->setPlaceholderText("Enter expression...");
    
    QGroupBox* displayGroup = new QGroupBox("Display");
    QVBoxLayout* displayLayout = new QVBoxLayout();
    displayLayout->addWidget(display);
    displayLayout->addWidget(expressionLine);
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
    historyLayout->addWidget(historyLabel);
    
    QTextEdit* historyTextEdit = new QTextEdit();
    historyTextEdit->setReadOnly(true);
    historyTextEdit->setMaximumHeight(400);
    historyTextEdit->setAcceptRichText(false);
    
    historyLayout->addWidget(historyTextEdit);
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
    });
    connect(keypad, &KeypadWidget::historyToggled, this, &CalculatorWindow::onHistoryToggled);
    
    QShortcut* shortcutClear = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(shortcutClear, &QShortcut::activated, this, [this]() {
        onClearClicked();
    });
    
    QShortcut* shortcutBackspace = new QShortcut(QKeySequence(Qt::Key_Back), this);
    connect(shortcutBackspace, &QShortcut::activated, this, [this]() {
        onBackspaceClicked();
    });
    
    QShortcut* shortcutEquals = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(shortcutEquals, &QShortcut::activated, this, [this]() {
        if (!currentExpression.isEmpty()) onEqualsClicked();
    });
    
    QShortcut* shortcutHistory = new QShortcut(QKeySequence(Qt::Key_H), this);
    connect(shortcutHistory, &QShortcut::activated, this, [this]() {
        onHistoryToggled();
    });
    
    QShortcut* shortcutToggleTheme = new QShortcut(QKeySequence(Qt::Key_T), this);
    connect(shortcutToggleTheme, &QShortcut::activated, this, [this]() {
        static bool dark = false;
        dark = !dark;
        onThemeChanged();
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

ThemeManager CalculatorWindow::getTheme() const {
    return themeManager;
}

void CalculatorWindow::onNumberClicked() {
    emit keypad->numberClicked();
}

void CalculatorWindow::onOperatorClicked() {
    emit keypad->operatorClicked();
}

void CalculatorWindow::onFunctionClicked() {
    emit keypad->functionClicked();
}

void CalculatorWindow::onClearClicked() {
    currentExpression.clear();
    display->clearDisplay();
    expressionLine->clear();
}

void CalculatorWindow::onBackspaceClicked() {
    if (!currentExpression.isEmpty()) {
        currentExpression.removeLast();
        display->displayResult(QString::fromUtf8(currentExpression.toStdString().c_str()));
    }
}

void CalculatorWindow::onEqualsClicked() {
    try {
        double result = engine.calculate(currentExpression.toStdString());
        std::string resultStr = std::to_string(result);
        
        QString displayResult(QString::fromStdString(resultStr));
        display->displayResult(displayResult);
        
        std::string historyEntry = currentExpression.toStdString() + " = " + resultStr;
        engine.addToMemory(result);
        
        updateHistory();
        
        currentExpression.clear();
        displayResult.clear();
    } catch (const std::exception& e) {
        display->displayResult("Error: " + QString::fromStdString(e.what()));
    }
}

void CalculatorWindow::onMemoryAdd() {
    try {
        double current = engine.getMemory();
        engine.setMemory(current + 1);
        QString memDisplay = QString("M = %1").arg(current + 1, 0, 'f', 2);
        display->displayResult(memDisplay);
    } catch (...) {
        display->displayResult("Memory Error");
    }
}

void CalculatorWindow::onMemorySubtract() {
    try {
        double current = engine.getMemory();
        engine.setMemory(current - 1);
        QString memDisplay = QString("M = %1").arg(current - 1, 0, 'f', 2);
        display->displayResult(memDisplay);
    } catch (...) {
        display->displayResult("Memory Error");
    }
}

void CalculatorWindow::onMemoryRecall() {
    display->displayResult(QString::number(engine.getMemory()));
}

void CalculatorWindow::onMemoryStore() {
    try {
        std::string storedValue = engine.getLastResult();
        QString memDisplay = QString("Memory stored: %1").arg(QString::fromStdString(storedValue));
        display->displayResult(memDisplay);
    } catch (...) {
        display->displayResult("Store Error");
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
    expressionLine->setText(currentExpression);
}

void CalculatorWindow::updateHistory() {
    QString history = QString::fromStdString(engine.getHistory());
    QTextEdit* historyText = historyArea->findChild<QTextEdit*>();
    if (historyText) {
        historyText->setText(history);
    }
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
