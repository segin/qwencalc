#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QColor>
#include <QString>
#include <QMap>

namespace qwencalc {

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

private:
    QGridLayout* layout;
    QMap<QString, QPushButton*> buttons;
    
    void createButtons();
    void setupConnections();
};

} // namespace qwencalc

#endif // KEYPAD_WIDGET_H
