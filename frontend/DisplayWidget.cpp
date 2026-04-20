#include "DisplayWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <memory>
#include <QFont>
#include <QPalette>

namespace qwencalc {

    DisplayWidget::DisplayWidget(QWidget* parent)
    : QWidget(parent) {
    resultLabel = new QLineEdit(this);
    expressionLabel = new QLineEdit(this);
    
    resultLabel->setReadOnly(true);
    resultLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    resultLabel->setFont(QFont("Arial", 36, QFont::Bold));
    resultLabel->setPlaceholderText("0");
    
    expressionLabel->setReadOnly(true);
    expressionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    expressionLabel->setFont(QFont("Arial", 14));
    expressionLabel->setPlaceholderText("Expression");
    
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    
    QVBoxLayout* displayBox = new QVBoxLayout();
    displayBox->addWidget(expressionLabel);
    displayBox->addWidget(resultLabel);
    displayBox->setSpacing(5);
    
    mainLayout->addLayout(displayBox);
    
    setMinimumHeight(200);
    
    QPalette bgPalette = palette();
    bgPalette.setColor(QPalette::Window, Qt::black);
    setPalette(bgPalette);
    
    connect(resultLabel, &QLineEdit::textChanged, this, &DisplayWidget::onTextChanged);
    connect(expressionLabel, &QLineEdit::textChanged, this, &DisplayWidget::onTextChanged);
}

void DisplayWidget::displayResult(const QString& result) {
    resultLabel->setText(result);
}

void DisplayWidget::displayExpression(const QString& expression) {
    expressionLabel->setText(expression);
}

void DisplayWidget::clearDisplay() {
    resultLabel->clear();
    expressionLabel->clear();
}

void DisplayWidget::setTheme(const QString& themeName) {
    if (themeName == "light") {
        QPalette bgPalette = palette();
        bgPalette.setColor(QPalette::Window, QColor("#f0f0f0"));
        setPalette(bgPalette);
        resultLabel->setStyleSheet("QLineEdit { color: #000000; font-size: 36px; }");
        expressionLabel->setStyleSheet("QLineEdit { color: #333333; }");
    } else if (themeName == "blue") {
        QPalette bgPalette = palette();
        bgPalette.setColor(QPalette::Window, QColor("#1a2a4a"));
        setPalette(bgPalette);
        resultLabel->setStyleSheet("QLineEdit { color: #ffffff; font-size: 36px; }");
        expressionLabel->setStyleSheet("QLineEdit { color: #aaddff; }");
    } else {
        QPalette bgPalette = palette();
        bgPalette.setColor(QPalette::Window, QColor("#1e1e1e"));
        setPalette(bgPalette);
        resultLabel->setStyleSheet("QLineEdit { color: #ffffff; font-size: 36px; }");
        expressionLabel->setStyleSheet("QLineEdit { color: #888888; }");
    }
}

void DisplayWidget::setTextColor(const QColor& color) {
    resultLabel->setStyleSheet("QLineEdit { color: " + color.name() + "; }");
    expressionLabel->setStyleSheet("QLineEdit { color: " + color.name() + "; }");
}

void DisplayWidget::setBackgroundColor(const QColor& color) {
    QPalette bgPalette = palette();
    bgPalette.setColor(QPalette::Window, color);
    setPalette(bgPalette);
}

QString DisplayWidget::getResult() const {
    return resultLabel->text();
}

QString DisplayWidget::getExpression() const {
    return expressionLabel->text();
}

void DisplayWidget::onTextChanged() {
    QString text = resultLabel->text();
    if (text.isEmpty()) {
        expressionLabel->clear();
    }
}

} // namespace qwencalc
