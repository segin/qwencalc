#include "ThemeManager.h"
#include <QtWidgets>

namespace qwencalc {

ThemeManager::ThemeManager() : currentTheme("dark"), settings(nullptr) {
    initializeDefaultThemes();
}

ThemeManager::~ThemeManager() { delete settings; }

void ThemeManager::initializeDefaultThemes() {
    colors["background"] = QColor("#1e1e1e");
    colors["text"] = QColor("#ffffff");
    colors["button"] = QColor("#4a4a4a");
    colors["buttonHover"] = QColor("#5a5a5a");
    colors["buttonPressed"] = QColor("#3a3a3a");
    colors["displayBackground"] = QColor("#000000");
    colors["displayText"] = QColor("#ffffff");
}

void ThemeManager::loadTheme(const QString &themeName) {
    currentTheme = themeName;
    if (themeName == "light") {
        colors["background"] = QColor("#f0f0f0");
        colors["text"] = QColor("#333333");
        colors["button"] = QColor("#cccccc");
        colors["buttonHover"] = QColor("#bbbbbb");
        colors["buttonPressed"] = QColor("#aaaaaa");
        colors["displayBackground"] = QColor("#ffffff");
        colors["displayText"] = QColor("#000000");
    } else if (themeName == "dark") {
        colors["background"] = QColor("#1e1e1e");
        colors["text"] = QColor("#ffffff");
        colors["button"] = QColor("#4a4a4a");
        colors["buttonHover"] = QColor("#5a5a5a");
        colors["buttonPressed"] = QColor("#3a3a3a");
        colors["displayBackground"] = QColor("#000000");
        colors["displayText"] = QColor("#ffffff");
    } else if (themeName == "blue") {
        colors["background"] = QColor("#1a2a4a");
        colors["text"] = QColor("#aaddff");
        colors["button"] = QColor("#2a4a6a");
        colors["buttonHover"] = QColor("#3a5a7a");
        colors["buttonPressed"] = QColor("#1a3a5a");
        colors["displayBackground"] = QColor("#0a1a3a");
        colors["displayText"] = QColor("#ffffff");
    }
}

void ThemeManager::saveTheme(const QString &themeName) {
    currentTheme = themeName;
}

void ThemeManager::deleteTheme(const QString &themeName) {
    if (currentTheme == themeName) {
        initializeDefaultThemes();
        currentTheme = "dark";
    }
}

QList<QString> ThemeManager::listThemes() {
    QList<QString> themes;
    themes.append("dark");
    themes.append("light");
    themes.append("blue");
    return themes;
}

QColor ThemeManager::getBackgroundColor() const { return colors["background"]; }

QColor ThemeManager::getTextColor() const { return colors["text"]; }

QColor ThemeManager::getButtonColor() const { return colors["button"]; }

QColor ThemeManager::getButtonHoverColor() const {
    return colors["buttonHover"];
}

QColor ThemeManager::getButtonPressedColor() const {
    return colors["buttonPressed"];
}

QColor ThemeManager::getDisplayBackground() const {
    return colors["displayBackground"];
}

QColor ThemeManager::getDisplayText() const { return colors["displayText"]; }

void ThemeManager::setBackgroundColor(const QColor &color) {
    colors["background"] = color;
}

void ThemeManager::setTextColor(const QColor &color) { colors["text"] = color; }

void ThemeManager::setButtonColor(const QColor &color) {
    colors["button"] = color;
}

void ThemeManager::setButtonHoverColor(const QColor &color) {
    colors["buttonHover"] = color;
}

void ThemeManager::setButtonPressedColor(const QColor &color) {
    colors["buttonPressed"] = color;
}

void ThemeManager::setDisplayBackground(const QColor &color) {
    colors["displayBackground"] = color;
}

void ThemeManager::setDisplayText(const QColor &color) {
    colors["displayText"] = color;
}

void ThemeManager::applyThemeToWidget(QWidget *widget) {
    if (!widget)
        return;
    QPalette palette;
    palette.setColor(QPalette::Window, colors["background"]);
    palette.setColor(QPalette::Text, colors["text"]);
    widget->setPalette(palette);
}

QString ThemeManager::getCurrentTheme() const { return currentTheme; }

QList<QString> ThemeManager::getAvailableThemes() const {
    QList<QString> themes;
    themes.append("dark");
    themes.append("light");
    themes.append("blue");
    return themes;
}

} // namespace qwencalc
