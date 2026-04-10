#include "KeypadWidget.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QColor>

namespace qwencalc {

KeypadWidget::KeypadWidget(QWidget* parent)
    : QWidget(parent) {
    layout = new QGridLayout(this);
    createButtons();
    setupConnections();
}

void KeypadWidget::createButtons() {
    int row = 0;
    int col = 0;
    
    buttons["sin"] = addButton("sin", "function", QColor("#4a4a4a"));
    buttons["cos"] = addButton("cos", "function", QColor("#4a4a4a"));
    buttons["tan"] = addButton("tan", "function", QColor("#4a4a4a"));
    buttons["log"] = addButton("log", "function", QColor("#4a4a4a"));
    buttons["ln"] = addButton("ln", "function", QColor("#4a4a4a"));
    buttons["sqrt"] = addButton("sqrt", "function", QColor("#4a4a4a"));
    buttons["pow"] = addButton("x^y", "function", QColor("#4a4a4a"));
    buttons["factorial"] = addButton("x!", "function", QColor("#4a4a4a"));
    
    buttons["7"] = addButton("7", "number", QColor("#5a5a5a"));
    buttons["8"] = addButton("8", "number", QColor("#5a5a5a"));
    buttons["9"] = addButton("9", "number", QColor("#5a5a5a"));
    buttons["4"] = addButton("4", "number", QColor("#5a5a5a"));
    buttons["5"] = addButton("5", "number", QColor("#5a5a5a"));
    buttons["6"] = addButton("6", "number", QColor("#5a5a5a"));
    buttons["1"] = addButton("1", "number", QColor("#5a5a5a"));
    buttons["2"] = addButton("2", "number", QColor("#5a5a5a"));
    buttons["3"] = addButton("3", "number", QColor("#5a5a5a"));
    buttons["0"] = addButton("0", "number", QColor("#5a5a5a"));
    
    buttons["clear"] = addButton("C", "operator", QColor("#8b0000"));
    buttons["backspace"] = addButton("⌫", "operator", QColor("#8b0000"));
    buttons["divide"] = addButton("/", "operator", QColor("#ff6b6b"));
    buttons["multiply"] = addButton("*", "operator", QColor("#ff6b6b"));
    buttons["subtract"] = addButton("-", "operator", QColor("#ff6b6b"));
    buttons["add"] = addButton("+", "operator", QColor("#ff6b6b"));
    buttons["equals"] = addButton("=", "operator", QColor("#4caf50"));
    buttons["dot"] = addButton(".", "number", QColor("#5a5a5a"));
    buttons["memory"] = addButton("MEM", "operator", QColor("#4a4a4a"));
    buttons["history"] = addButton("HIST", "operator", QColor("#4a4a4a"));
    
    layout->addWidget(buttons["sin"], row, col++, 1, 1);
    layout->addWidget(buttons["cos"], row, col++, 1, 1);
    layout->addWidget(buttons["tan"], row, col++, 1, 1);
    layout->addWidget(buttons["log"], row, col++, 1, 1);
    
    row++; col = 0;
    buttons["7"]->setText("7");
    buttons["8"]->setText("8");
    buttons["9"]->setText("9");
    buttons["4"]->setText("4");
    buttons["5"]->setText("5");
    buttons["6"]->setText("6");
    buttons["1"]->setText("1");
    buttons["2"]->setText("2");
    buttons["3"]->setText("3");
    buttons["0"]->setText("0");
    
    buttons["7"]->setMaximumHeight(40);
    buttons["8"]->setMaximumHeight(40);
    buttons["9"]->setMaximumHeight(40);
    buttons["4"]->setMaximumHeight(40);
    buttons["5"]->setMaximumHeight(40);
    buttons["6"]->setMaximumHeight(40);
    buttons["1"]->setMaximumHeight(40);
    buttons["2"]->setMaximumHeight(40);
    buttons["3"]->setMaximumHeight(40);
    buttons["0"]->setMaximumHeight(40);
    
    layout->addWidget(buttons["7"], row, col++, 2, 1);
    layout->addWidget(buttons["8"], row, col++, 2, 1);
    layout->addWidget(buttons["9"], row, col++, 2, 1);
    
    row++; col = 3;
    layout->addWidget(buttons["sqrt"], row, col++, 2, 1);
    layout->addWidget(buttons["pow"], row, col++, 2, 1);
    
    row++; col = 0;
    buttons["clear"]->setText("C");
    buttons["backspace"]->setText("⌫");
    buttons["memory"]->setText("MEM");
    buttons["history"]->setText("HIST");
    
    buttons["clear"]->setMaximumHeight(40);
    buttons["backspace"]->setMaximumHeight(40);
    buttons["memory"]->setMaximumHeight(40);
    buttons["history"]->setMaximumHeight(40);
    
    buttons["divide"]->setText("÷");
    buttons["multiply"]->setText("×");
    buttons["subtract"]->setText("-");
    buttons["add"]->setText("+");
    buttons["equals"]->setText("=");
    buttons["dot"]->setText(".");
    
    buttons["divide"]->setMaximumHeight(40);
    buttons["multiply"]->setMaximumHeight(40);
    buttons["subtract"]->setMaximumHeight(40);
    buttons["add"]->setMaximumHeight(40);
    buttons["equals"]->setMaximumHeight(40);
    buttons["dot"]->setMaximumHeight(40);
    
    layout->addWidget(buttons["clear"], row, col++, 2, 1);
    layout->addWidget(buttons["backspace"], row, col++, 2, 1);
    layout->addWidget(buttons["divide"], row, col++, 2, 1);
    
    layout->addWidget(buttons["memory"], row + 1, 4, 1, 1);
    layout->addWidget(buttons["history"], row + 1, 5, 1, 1);
    
    layout->addWidget(buttons["factorial"], row + 2, 0, 1, 1);
    layout->addWidget(buttons["0"], row + 2, 1, 1, 2);
    layout->addWidget(buttons["dot"], row + 2, 3, 1, 1);
    layout->addWidget(buttons["equals"], row + 2, 4, 1, 2);
}

QPushButton* KeypadWidget::addButton(const QString& text, const QString& type, const QColor& color) {
    QPushButton* button = new QPushButton(this);
    button->setText(text);
    button->setMinimumSize(60, 60);
    button->setMaximumSize(80, 80);
    button->setStyleSheet("QPushButton { background-color: " + color.name() + "; color: white; font-size: 18px; font-weight: bold; } QPushButton:pressed { background-color: " + color.lighter(90).name() + "; }");
    return button;
}

void KeypadWidget::setupKeypad() {
    createButtons();
}

void KeypadWidget::setupConnections() {
    for (auto& button : buttons) {
        connect(button, &QPushButton::clicked, this, &KeypadWidget::onButtonClick);
    }
}

void KeypadWidget::onButtonClick() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    QString text = button->text();
    QString type;
    
    if (button->objectName().startsWith("btn") && button->objectName().length() > 3) {
        QString btnText = button->text();
        if (btnText == "sin" || btnText == "cos" || btnText == "tan" || btnText == "log" || btnText == "ln" || btnText == "sqrt" || btnText == "x^y" || btnText == "x!") {
            emit functionClicked(btnText);
            return;
        }
        if (btnText == "C") {
            emit clearClicked();
            return;
        }
        if (btnText == "⌫") {
            emit backspaceClicked();
            return;
        }
        if (btnText == "=") {
            emit equalsClicked();
            return;
        }
        if (btnText == "MEM") {
            emit memoryClicked("add");
            return;
        }
        if (btnText == "HIST") {
            emit historyToggled();
            return;
        }
        if (text == "+" || text == "-" || text == "×" || text == "÷" || text == "/") {
            emit operatorClicked(text);
            return;
        }
        if (text == "." || (text.length() == 1 && text.toLatin1() >= '0' && text.toLatin1() <= '9')) {
            emit numberClicked(text.toInt());
            return;
        }
    }
}

void KeypadWidget::setButtonColor(const QColor& color) {
    for (auto& button : buttons) {
        button->setStyleSheet("QPushButton { background-color: " + color.name() + "; color: white; }");
    }
}

void KeypadWidget::setTextColor(const QColor& color) {
    for (auto& button : buttons) {
        button->setStyleSheet("QPushButton { color: " + color.name() + "; }");
    }
}

void KeypadWidget::setButtonsEnabled(bool enabled) {
    for (auto& button : buttons) {
        button->setEnabled(enabled);
    }
}

void KeypadWidget::setButtonsDisabled(bool disabled) {
    for (auto& button : buttons) {
        button->setEnabled(!disabled);
    }
}

void KeypadWidget::setTheme(const QString& themeName) {
    for (auto& button : buttons) {
        button->setStyleSheet("QPushButton { background-color: " + QColor("#4a4a4a").name() + "; color: white; } QPushButton:pressed { background-color: " + QColor("#3a3a3a").name() + "; }");
    }
}

} // namespace qwencalc
