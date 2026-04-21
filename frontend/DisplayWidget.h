#pragma once

#include <QColor>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

namespace qwencalc {

class DisplayWidget : public QWidget {
    Q_OBJECT

  public:
    explicit DisplayWidget(QWidget *parent = nullptr);

    void displayResult(const QString &result);
    void displayExpression(const QString &expression);
    void clearDisplay();

    void setTheme(const QString &themeName);
    void setTextColor(const QColor &color);
    void setBackgroundColor(const QColor &color);

    QString getResult() const;
    QString getExpression() const;

  private slots:
    void onTextChanged();

  private:
    QLineEdit *resultLabel;
    QLineEdit *expressionLabel;

    QFont resultFont;
    QFont expressionFont;
};

} // namespace qwencalc
