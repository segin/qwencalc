#ifndef KEYPAD_WIDGET_H
#define KEYPAD_WIDGET_H

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
#include <QList>
#include <QVector>
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

namespace qwencalc {

class KeypadWidget : public QWidget {
    Q_OBJECT

public:
    explicit KeypadWidget(QWidget* parent = nullptr);
    
    void addButton(const QString& text, const QString& type, const QColor& color);
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

private slots:
    void onButtonClick();

private:
    QGridLayout* layout;
    QMap<QString, QPushButton*> buttons;
    
    QPushButton* btn7;
    QPushButton* btn8;
    QPushButton* btn9;
    QPushButton* btnDiv;
    QPushButton* btn4;
    QPushButton* btn5;
    QPushButton* btn6;
    QPushButton* btnMul;
    QPushButton* btn1;
    QPushButton* btn2;
    QPushButton* btn3;
    QPushButton* btnSub;
    QPushButton* btn0;
    QPushButton* btnDot;
    QPushButton* btnEquals;
    QPushButton* btnAdd;
    
    QPushButton* btnSin;
    QPushButton* btnCos;
    QPushButton* btnTan;
    QPushButton* btnSqrt;
    QPushButton* btnLog;
    QPushButton* btnLn;
    QPushButton* btnPow;
    QPushButton* btnFactorial;
    
    QPushButton* btnClear;
    QPushButton* btnBackspace;
    QPushButton* btnMemory;
    QPushButton* btnHistory;

    void createButtons();
    void setupConnections();
};

} // namespace qwencalc

#endif // KEYPAD_WIDGET_H
