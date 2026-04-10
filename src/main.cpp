#include <QApplication>
#include <QMainWindow>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
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
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "CalculatorWindow.h"
#include "DisplayWidget.h"
#include "KeypadWidget.h"
#include "ThemeManager.h"
#include "CalculatorEngine.h"
#include "ExpressionParser.h"
#include "HistoryManager.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    QCoreApplication::setApplicationName("QwenCalc");
    QCoreApplication::setApplicationVersion("0.1.0");
    QCoreApplication::setOrganizationName("QwenCalc");
    QCoreApplication::setOrganizationDomain("qwencalc.org");
    
    QCommandLineParser parser;
    parser.setApplicationDescription("A modern desktop calculator");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(QCommandLineOption(QStringList() << QString("t") << QString("theme"),
        QString("Theme"), "themeName", "dark", QString("dark")));
    parser.process(app);
    
    QString themeName = parser.value("theme");
    
    if (QFileInfo::exists("/home/segin/qwencalc/build")) {
        QString buildPath = "/home/segin/qwencalc/build";
        QStringList files = QDir(buildPath).entryList(QDir::Files);
        for (const QString& file : files) {
            qDebug() << "Found file:" << file;
        }
    }
    
    qwencalc::CalculatorWindow window;
    window.resize(400, 600);
    window.setWindowFlags(Qt::Window);
    
    window.applyTheme(themeName);
    window.show();
    
    return app.exec();
}
