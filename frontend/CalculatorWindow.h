#ifndef CALCULATOR_WINDOW_H
#define CALCULATOR_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QScrollArea>
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
    ThemeManager getTheme() const;

private slots:
    void onNumberClicked();
    void onOperatorClicked();
    void onFunctionClicked();
    void onClearClicked();
    void onBackspaceClicked();
    void onEqualsClicked();
    void onMemoryAdd();
    void onMemorySubtract();
    void onMemoryRecall();
    void onMemoryStore();
    void onHistoryToggled();
    void onThemeChanged();

private:
    DisplayWidget* display;
    KeypadWidget* keypad;
    QScrollArea* historyArea;
    QPushButton* memoryLabel;
    QLineEdit* expressionLine;

    CalculatorEngine engine;
    ThemeManager themeManager;
    bool historyVisible;
    QString currentExpression;

    void setupUI();
    void setupConnections();
    void updateDisplay();
    void updateHistory();
    void loadSettings();
    void saveSettings();
};

} // namespace qwencalc

#endif // CALCULATOR_WINDOW_H
