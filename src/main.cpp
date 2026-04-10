#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QTextEdit>
#include <QFont>
#include <QPalette>
#include <QColor>
#include <string>
#include "backend/CalculatorEngine.h"
#include "backend/ExpressionParser.h"
#include "backend/HistoryManager.h"
#include "frontend/DisplayWidget.h"
#include "frontend/KeypadWidget.h"
#include "frontend/ThemeManager.h"
#include "frontend/CalculatorWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    qwencalc::CalculatorWindow window;
    window.show();
    
    return app.exec();
}
