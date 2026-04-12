#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFont>
#include <QPalette>
#include <QColor>
#include <QString>
#include <QLabel>

namespace qwencalc {

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

} // namespace qwencalc

#endif // DISPLAY_WIDGET_H
