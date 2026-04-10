#include "ThemeManager.h"

namespace qwencalc {

ThemeManager::ThemeManager()
    : currentTheme("dark") {
    initializeDefaultThemes();
}

void ThemeManager::initializeDefaultThemes() {
    colors["background"] = QColor("#1e1e1e");
    colors["text"] = QColor("#ffffff");
    colors["button"] = QColor("#4a4a4a");
    colors["buttonHover"] = QColor("#5a5a5a");
    colors["buttonPressed"] = QColor("#3a3a3a");
    colors["displayBackground"] = QColor("#000000");
    colors["displayText"] = QColor("#ffffff");
}

void ThemeManager::loadTheme(const QString& themeName) {
    currentTheme = themeName;
}

void ThemeManager::saveTheme(const QString& themeName) {
    currentTheme = themeName;
}

void ThemeManager::deleteTheme(const QString& themeName) {
    colors.clear();
    initializeDefaultThemes();
}

void ThemeManager::listThemes() {
    qDebug() << "Available themes:" << currentTheme;
}

QColor ThemeManager::getBackgroundColor() const {
    return colors["background"];
}

QColor ThemeManager::getTextColor() const {
    return colors["text"];
}

QColor ThemeManager::getButtonColor() const {
    return colors["button"];
}

QColor ThemeManager::getButtonHoverColor() const {
    return colors["buttonHover"];
}

QColor ThemeManager::getButtonPressedColor() const {
    return colors["buttonPressed"];
}

QColor ThemeManager::getDisplayBackground() const {
    return colors["displayBackground"];
}

QColor ThemeManager::getDisplayText() const {
    return colors["displayText"];
}

void ThemeManager::setBackgroundColor(const QColor& color) {
    colors["background"] = color;
}

void ThemeManager::setTextColor(const QColor& color) {
    colors["text"] = color;
}

void ThemeManager::setButtonColor(const QColor& color) {
    colors["button"] = color;
}

void ThemeManager::setButtonHoverColor(const QColor& color) {
    colors["buttonHover"] = color;
}

void ThemeManager::setButtonPressedColor(const QColor& color) {
    colors["buttonPressed"] = color;
}

void ThemeManager::setDisplayBackground(const QColor& color) {
    colors["displayBackground"] = color;
}

void ThemeManager::setDisplayText(const QColor& color) {
    colors["displayText"] = color;
}

void ThemeManager::applyThemeToWidget(QWidget* widget) {
    if (widget) {
        QPalette bgPalette = widget->palette();
        bgPalette.setColor(QPalette::Window(colors["background"]));
        widget->setPalette(bgPalette);
    }
}

QString ThemeManager::getCurrentTheme() const {
    return currentTheme;
}

QList<QString> ThemeManager::getAvailableThemes() const {
    QList<QString> themes;
    themes.append("dark");
    themes.append("light");
    themes.append("blue");
    return themes;
}

} // namespace qwencalc
