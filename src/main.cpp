#include "backend/CalculatorEngine.h"
#include "backend/ExpressionParser.h"
#include "backend/HistoryManager.h"
#include "frontend/CalculatorWindow.h"
#include "frontend/DisplayWidget.h"
#include "frontend/KeypadWidget.h"
#include "frontend/ThemeManager.h"
#include <QApplication>
#include <QColor>
#include <QFont>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPalette>
#include <QPushButton>
#include <QScrollArea>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <string>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    qwencalc::CalculatorWindow window;
    window.show();

    return app.exec();
}
