#pragma once

#include <QColor>
#include <QFont>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <QPalette>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

namespace qwencalc {

class KeypadWidget : public QWidget {
    Q_OBJECT

  public:
    explicit KeypadWidget(QWidget *parent = nullptr);

    QPushButton *addButton(const QString &text, const QString &type,
                           const QColor &color);
    void setupKeypad();

    void setTheme(const QString &themeName);
    void setButtonColor(const QColor &color);
    void setTextColor(const QColor &color);

    void setButtonsEnabled(bool enabled);
    void setButtonsDisabled(bool disabled);

  signals:
    void numberClicked(int number);
    void operatorClicked(const QString &op);
    void functionClicked(const QString &func);
    void clearClicked();
    void equalsClicked();
    void backspaceClicked();
    void memoryClicked(const QString &action);
    void historyToggled();
    void dotClicked();
    void parenClicked(const QString &paren);
    void themeToggled();

  private slots:
    void onButtonClick();

  private:
    QGridLayout *layout;
    QMap<QString, QPushButton *> buttons;

    void createButtons();
    void setupConnections();
};

} // namespace qwencalc
