#include "KeypadWidget.h"
#include <QtWidgets>

namespace qwencalc {

KeypadWidget::KeypadWidget(QWidget *parent) : QWidget(parent) {
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
    buttons["sqrt"] = addButton("√", "function", QColor("#4a4a4a"));
    buttons["pow"] = addButton("x^y", "function", QColor("#4a4a4a"));
    buttons["factorial"] = addButton("x!", "function", QColor("#4a4a4a"));
    buttons["openParen"] = addButton("(", "paren", QColor("#4caf50"));
    buttons["closeParen"] = addButton(")", "paren", QColor("#4caf50"));

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
    buttons["divide"] = addButton("÷", "operator", QColor("#ff6b6b"));
    buttons["multiply"] = addButton("×", "operator", QColor("#ff6b6b"));
    buttons["subtract"] = addButton("-", "operator", QColor("#ff6b6b"));
    buttons["add"] = addButton("+", "operator", QColor("#ff6b6b"));
    buttons["equals"] = addButton("=", "operator", QColor("#4caf50"));
    buttons["dot"] = addButton(".", "number", QColor("#5a5a5a"));
    buttons["MC"] = addButton("MC", "memory", QColor("#ff9800"));
    buttons["MR"] = addButton("MR", "memory", QColor("#ff9800"));
    buttons["MS"] = addButton("MS", "memory", QColor("#ff9800"));
    buttons["M+"] = addButton("M+", "memory", QColor("#ff9800"));
    buttons["M-"] = addButton("M-", "memory", QColor("#ff9800"));
    buttons["history"] = addButton("HIST", "operator", QColor("#4a4a4a"));
    buttons["theme"] = addButton("🌗", "operator", QColor("#6a6a6a"));

    // Row 1: Scientific functions (5 buttons)
    layout->addWidget(buttons["sin"], row, col++, 1, 1);
    layout->addWidget(buttons["cos"], row, col++, 1, 1);
    layout->addWidget(buttons["tan"], row, col++, 1, 1);
    layout->addWidget(buttons["log"], row, col++, 1, 1);
    layout->addWidget(buttons["ln"], row, col++, 1, 1);

    // Row 2: Scientific functions + parentheses (5 buttons)
    row++;
    col = 0;
    layout->addWidget(buttons["sqrt"], row, col++, 1, 1);
    layout->addWidget(buttons["pow"], row, col++, 1, 1);
    layout->addWidget(buttons["factorial"], row, col++, 1, 1);
    layout->addWidget(buttons["openParen"], row, col++, 1, 1);
    layout->addWidget(buttons["closeParen"], row, col++, 1, 1);

    // Row 3: Number keys + memory + history (6 buttons)
    row++;
    col = 0;
    layout->addWidget(buttons["7"], row, col++, 1, 1);
    layout->addWidget(buttons["8"], row, col++, 1, 1);
    layout->addWidget(buttons["9"], row, col++, 1, 1);
    layout->addWidget(buttons["MC"], row, col++, 1, 1);
    layout->addWidget(buttons["MR"], row, col++, 1, 1);
    layout->addWidget(buttons["MS"], row, col++, 1, 1);

    // Row 4: Number keys + memory (6 buttons)
    row++;
    col = 0;
    layout->addWidget(buttons["4"], row, col++, 1, 1);
    layout->addWidget(buttons["5"], row, col++, 1, 1);
    layout->addWidget(buttons["6"], row, col++, 1, 1);
    layout->addWidget(buttons["M+"], row, col++, 1, 1);
    layout->addWidget(buttons["M-"], row, col++, 1, 1);
    layout->addWidget(buttons["history"], row, col++, 1, 1);
    layout->addWidget(buttons["theme"], row, col++, 1, 1);

    // Row 5: Number keys + operators (6 buttons)
    row++;
    col = 0;
    layout->addWidget(buttons["1"], row, col++, 1, 1);
    layout->addWidget(buttons["2"], row, col++, 1, 1);
    layout->addWidget(buttons["3"], row, col++, 1, 1);
    layout->addWidget(buttons["backspace"], row, col++, 1, 1);
    layout->addWidget(buttons["divide"], row, col++, 1, 1);
    layout->addWidget(buttons["add"], row, col++, 1, 1);
    row++;
    col = 0;
    layout->addWidget(buttons["0"], row, col++, 1, 1);
    layout->addWidget(buttons["dot"], row, col++, 1, 1);
    layout->addWidget(buttons["equals"], row, col++, 1, 1);
    layout->addWidget(buttons["clear"], row, col++, 1, 1);
    layout->addWidget(buttons["subtract"], row, col++, 1, 1);
    layout->addWidget(buttons["multiply"], row, col++, 1, 1);
}

QPushButton *KeypadWidget::addButton(const QString &text, const QString &,
                                     const QColor &color) {
    QPushButton *button = new QPushButton(this);
    button->setText(text);
    button->setMinimumSize(45, 45);
    button->setMaximumSize(60, 60);
    button->setStyleSheet("QPushButton { background-color: " + color.name() +
                          "; color: white; font-size: 14px; font-weight: bold; "
                          "} QPushButton:pressed { background-color: " +
                          color.lighter(90).name() + "; }");
    return button;
}

void KeypadWidget::setupKeypad() { createButtons(); }

void KeypadWidget::setupConnections() {
    for (auto &button : buttons) {
        connect(button, &QPushButton::clicked, this,
                &KeypadWidget::onButtonClick);
    }
}

void KeypadWidget::onButtonClick() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;

    QString text = button->text();

    if (text == "sin" || text == "cos" || text == "tan" || text == "log" ||
        text == "ln" || text == "sqrt" || text == "x^y" || text == "x!") {
        emit functionClicked(text);
        return;
    }
    if (text == "(" || text == ")") {
        emit parenClicked(text);
        return;
    }
    if (text == "C") {
        emit clearClicked();
        return;
    }
    if (text == "⌫") {
        emit backspaceClicked();
        return;
    }
    if (text == "=") {
        emit equalsClicked();
        return;
    }
    if (text == "MC") {
        emit memoryClicked("clear");
        return;
    }
    if (text == "MR") {
        emit memoryClicked("recall");
        return;
    }
    if (text == "MS") {
        emit memoryClicked("store");
        return;
    }
    if (text == "M+") {
        emit memoryClicked("add");
        return;
    }
    if (text == "M-") {
        emit memoryClicked("subtract");
        return;
    }
    if (text == "HIST") {
        emit historyToggled();
        return;
    }
    if (text == "🌗") {
        emit themeToggled();
        return;
    }
    if (text == "+" || text == "−" || text == "×" || text == "÷" ||
        text == "/" || text == "-") {
        QString asciiOp = text;
        if (text == "×")
            asciiOp = "*";
        else if (text == "÷")
            asciiOp = "/";
        else if (text == "−" || text == "-")
            asciiOp = "-";
        emit operatorClicked(asciiOp);
        return;
    }
    if (text == ".") {
        emit dotClicked();
        return;
    }
    if (text.length() == 1 && text >= "0" && text <= "9") {
        emit numberClicked(text.toInt());
        return;
    }
}

void KeypadWidget::setButtonColor(const QColor &color) {
    for (auto &button : buttons) {
        button->setStyleSheet("QPushButton { background-color: " +
                              color.name() + "; color: white; }");
    }
}

void KeypadWidget::setTextColor(const QColor &color) {
    for (auto &button : buttons) {
        button->setStyleSheet("QPushButton { color: " + color.name() + "; }");
    }
}

void KeypadWidget::setButtonsEnabled(bool enabled) {
    for (auto &button : buttons) {
        button->setEnabled(enabled);
    }
}

void KeypadWidget::setButtonsDisabled(bool disabled) {
    for (auto &button : buttons) {
        button->setEnabled(!disabled);
    }
}

void KeypadWidget::setTheme(const QString &) {
    for (auto &button : buttons) {
        button->setStyleSheet(
            "QPushButton { background-color: " + QColor("#4a4a4a").name() +
            "; color: white; } QPushButton:pressed { background-color: " +
            QColor("#3a3a3a").name() + "; }");
    }
}

} // namespace qwencalc
