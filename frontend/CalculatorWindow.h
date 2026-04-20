#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QScrollArea>
#include <QTextEdit>
#include <QApplication>
#include "DisplayWidget.h"
#include "KeypadWidget.h"
#include "ThemeManager.h"
#include "CalculatorEngine.h"

namespace qwencalc {

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
    DisplayWidget* display;
    KeypadWidget* keypad;
    QScrollArea* historyArea;
    QTextEdit* historyTextEdit;

    CalculatorEngine engine;
    ThemeManager themeManager;
    bool historyVisible;
    QString currentExpression;
    QString currentMemoryDisplay;
    QLabel* memoryLabelWidget;

    void setupUI();
    void setupConnections();
    void setupShortcuts();
    void updateDisplay();
    void updateHistory();
    void loadSettings();
    void saveSettings();
    void closeEvent(QCloseEvent* event) override;
};

} // namespace qwencalc
