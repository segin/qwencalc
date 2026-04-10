#ifndef DISPLAY_WIDGET_H
#define DISPLAY_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QFont>
#include <QPalette>
#include <QColor>
#include <QString>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QApplication>
#include <QDesktopServices>
#include <QProcessEnvironment>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QTimer>
#include <QMutex>
#include <QSemaphore>
#include <QQueue>
#include <QStack>
#include <QVector>
#include <QList>
#include <QMap>
#include <QHash>
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
#include <QVariant>
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
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

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
    QTextEdit* expressionTextEdit;
    QTextEdit* historyTextEdit;
    
    QFont resultFont;
    QFont expressionFont;
    QFont historyFont;
};

} // namespace qwencalc

#endif // DISPLAY_WIDGET_H
