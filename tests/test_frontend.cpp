#include "CalculatorWindow.h"
#include "DisplayWidget.h"
#include "KeypadWidget.h"
#include "ThemeManager.h"
#include <QApplication>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QTextEdit>
#include <QWidget>
#include <gtest/gtest.h>

using namespace qwencalc;

// Base fixture with QApplication for all Qt widgets
class QtWidgetFixture : public ::testing::Test {
  protected:
    int argc = 0;
    char *argv = nullptr;
    QApplication app{argc, &argv};

    void SetUp() override {
        display = new DisplayWidget();
        keypad = new KeypadWidget();
        window = new CalculatorWindow();
    }

    void TearDown() override {
        delete window;
        delete keypad;
        delete display;
    }

    DisplayWidget *display;
    KeypadWidget *keypad;
    CalculatorWindow *window;
};

// ThemeManagerFixture is separate because it tests ThemeManager directly
// without Qt widgets
class ThemeManagerFixture : public ::testing::Test {
  protected:
    ThemeManager manager;
    int argc = 0;
    char *argv = nullptr;
    QApplication app{argc, &argv};
};

TEST_F(ThemeManagerFixture, testConstruction) {
    EXPECT_EQ(manager.getCurrentTheme(), QString("dark"));
}

TEST_F(ThemeManagerFixture, testLoadDarkTheme) {
    manager.loadTheme("dark");
    EXPECT_EQ(manager.getCurrentTheme(), QString("dark"));
    EXPECT_EQ(manager.getBackgroundColor(), QColor("#1e1e1e"));
    EXPECT_EQ(manager.getTextColor(), QColor("#ffffff"));
}

TEST_F(ThemeManagerFixture, testLoadLightTheme) {
    manager.loadTheme("light");
    EXPECT_EQ(manager.getCurrentTheme(), QString("light"));
    EXPECT_EQ(manager.getBackgroundColor(), QColor("#f0f0f0"));
    EXPECT_EQ(manager.getTextColor(), QColor("#333333"));
}

TEST_F(ThemeManagerFixture, testLoadBlueTheme) {
    manager.loadTheme("blue");
    EXPECT_EQ(manager.getCurrentTheme(), QString("blue"));
    EXPECT_EQ(manager.getBackgroundColor(), QColor("#1a2a4a"));
    EXPECT_EQ(manager.getTextColor(), QColor("#aaddff"));
}

TEST_F(ThemeManagerFixture, testGetCurrentTheme) {
    EXPECT_EQ(manager.getCurrentTheme(), QString("dark"));
    manager.loadTheme("light");
    EXPECT_EQ(manager.getCurrentTheme(), QString("light"));
}

TEST_F(ThemeManagerFixture, testGetAvailableThemes) {
    QList<QString> themes = manager.getAvailableThemes();
    EXPECT_EQ(themes.size(), 3);
    EXPECT_TRUE(themes.contains("dark"));
    EXPECT_TRUE(themes.contains("light"));
    EXPECT_TRUE(themes.contains("blue"));
}

TEST_F(ThemeManagerFixture, testListThemes) {
    QList<QString> themes = manager.listThemes();
    EXPECT_EQ(themes.size(), 3);
    EXPECT_TRUE(themes.contains("dark"));
    EXPECT_TRUE(themes.contains("light"));
    EXPECT_TRUE(themes.contains("blue"));
}

TEST_F(ThemeManagerFixture, testSetBackgroundColor) {
    manager.setBackgroundColor(QColor("#ff0000"));
    EXPECT_EQ(manager.getBackgroundColor(), QColor("#ff0000"));
}

TEST_F(ThemeManagerFixture, testSetTextColor) {
    manager.setTextColor(QColor("#00ff00"));
    EXPECT_EQ(manager.getTextColor(), QColor("#00ff00"));
}

TEST_F(ThemeManagerFixture, testApplyThemeToWidget) {
    QWidget *widget = new QWidget();
    manager.applyThemeToWidget(widget);
    delete widget;
}

TEST_F(ThemeManagerFixture, testDeleteTheme) {
    manager.loadTheme("blue");
    EXPECT_EQ(manager.getCurrentTheme(), QString("blue"));
    manager.loadTheme("dark");
    EXPECT_EQ(manager.getCurrentTheme(), QString("dark"));
}

TEST_F(QtWidgetFixture, testDisplayWidgetConstruction) {
    EXPECT_NE(display, nullptr);
}

TEST_F(QtWidgetFixture, testDisplayWidgetResult) {
    display->displayResult("42");
    EXPECT_EQ(display->getResult(), "42");
}

TEST_F(QtWidgetFixture, testDisplayWidgetExpression) {
    display->displayExpression("2 + 2");
    EXPECT_EQ(display->getExpression(), "2 + 2");
}

TEST_F(QtWidgetFixture, testDisplayWidgetClear) {
    display->displayResult("100");
    display->displayExpression("5 + 5");
    display->clearDisplay();
    EXPECT_TRUE(display->getResult().isEmpty());
    EXPECT_TRUE(display->getExpression().isEmpty());
}

TEST_F(QtWidgetFixture, testDisplayWidgetTheme) {
    display->setTheme("light");
    display->setTheme("dark");
    display->setTheme("blue");
}

TEST_F(QtWidgetFixture, testDisplayWidgetTextColor) {
    display->setTextColor(QColor("#ff0000"));
    display->setTextColor(QColor("#00ff00"));
}

TEST_F(QtWidgetFixture, testDisplayWidgetBackgroundColor) {
    display->setBackgroundColor(QColor("#1e1e1e"));
    display->setBackgroundColor(QColor("#f0f0f0"));
}

TEST_F(QtWidgetFixture, testDisplayWidgetLongResult) {
    display->displayResult("1234567890123456789012345678901234567890");
    EXPECT_EQ(display->getResult(), "1234567890123456789012345678901234567890");
}

TEST_F(QtWidgetFixture, testKeypadWidgetConstruction) {
    EXPECT_NE(keypad, nullptr);
}

TEST_F(QtWidgetFixture, testKeypadWidgetAddButton) {
    QPushButton *btn =
        keypad->addButton("test", "test_type", QColor("#ffffff"));
    EXPECT_NE(btn, nullptr);
}

TEST_F(QtWidgetFixture, testKeypadWidgetTheme) {
    keypad->setTheme("light");
    keypad->setTheme("dark");
    keypad->setTheme("blue");
}

TEST_F(QtWidgetFixture, testKeypadWidgetTextColor) {
    keypad->setTextColor(QColor("#ffffff"));
    keypad->setTextColor(QColor("#000000"));
}

TEST_F(QtWidgetFixture, testKeypadWidgetButtonColor) {
    keypad->setButtonColor(QColor("#ff0000"));
    keypad->setButtonColor(QColor("#00ff00"));
}

TEST_F(QtWidgetFixture, testKeypadWidgetButtonsEnabled) {
    keypad->setButtonsEnabled(true);
    keypad->setButtonsEnabled(false);
    keypad->setButtonsEnabled(true);
}

TEST_F(QtWidgetFixture, testKeypadWidgetButtonsDisabled) {
    keypad->setButtonsDisabled(true);
    keypad->setButtonsDisabled(false);
}

TEST_F(QtWidgetFixture, testCalculatorWindowConstruction) {
    EXPECT_NE(window, nullptr);
}

TEST_F(QtWidgetFixture, testCalculatorWindowTheme) {
    ThemeManager &theme = window->getTheme();
    EXPECT_EQ(theme.getCurrentTheme(), QString("dark"));
}

TEST_F(QtWidgetFixture, testCalculatorWindowApplyTheme) {
    window->applyTheme("dark");
    window->applyTheme("light");
}

TEST_F(QtWidgetFixture, testCalculatorWindowApplyThemeBlue) {
    window->applyTheme("blue");
}
