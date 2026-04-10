#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include <QColor>
#include <QPalette>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QString>
#include <QMap>
#include <QList>
#include <QVariant>
#include <QByteArray>
#include <QPoint>
#include <QRect>
#include <QSize>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QShowEvent>
#include <QHideEvent>
#include <QTimerEvent>
#include <QChildEvent>
#include <QMetaEvent>
#include <QStaticMetaType>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPathItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsSvgItem>
#include <QGraphicsFrameItem>
#include <QGraphicsLayoutItem>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>

namespace qwencalc {

class ThemeManager {
public:
    ThemeManager();
    
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

#endif // THEME_MANAGER_H
