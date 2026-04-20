#pragma once

#include <QColor>
#include <QPalette>
#include <QSettings>
#include <QString>
#include <QMap>
#include <QList>

namespace qwencalc {

class ThemeManager {
public:
    ThemeManager();
    ~ThemeManager();
    
    void loadTheme(const QString& themeName);
    void saveTheme(const QString& themeName);
    void deleteTheme(const QString& themeName);
    void listThemes();
    
    QColor getBackgroundColor() const;
    QColor getTextColor() const;
    QColor getButtonColor() const;
    QColor getButtonHoverColor() const;
    QColor getButtonPressedColor() const;
    QColor getDisplayBackground() const;
    QColor getDisplayText() const;
    
    void setBackgroundColor(const QColor& color);
    void setTextColor(const QColor& color);
    void setButtonColor(const QColor& color);
    void setButtonHoverColor(const QColor& color);
    void setButtonPressedColor(const QColor& color);
    void setDisplayBackground(const QColor& color);
    void setDisplayText(const QColor& color);
    
    void applyThemeToWidget(QWidget* widget);
    
    QString getCurrentTheme() const;
    QList<QString> getAvailableThemes() const;

private:
    QMap<QString, QColor> colors;
    QString currentTheme;
    QSettings* settings;
    
    void initializeDefaultThemes();
    void saveColor(const QString& key, const QColor& color);
    QColor loadColor(const QString& key) const;
};

} // namespace qwencalc
