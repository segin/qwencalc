#include "CalculatorEngine.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <algorithm>

namespace qwencalc {

CalculatorEngine::CalculatorEngine()
    : memory(0.0), precision(10) {
}

double CalculatorEngine::calculate(const std::string& expression) {
    double result = 0.0;
    
    try {
        result = parser.parse(expression);
        lastResult = std::to_string(result);
        lastExpression = expression;
        
        historyManager.addEntry(expression, result);
    } catch (const ExpressionError& e) {
        lastResult = "Error";
        lastExpression = expression;
        historyManager.addEntry(expression, 0.0);
    }
    
    return result;
}

void CalculatorEngine::clear() {
    memory = 0.0;
    precision = 10;
}

void CalculatorEngine::clearHistory() {
    historyManager.clear();
    lastResult.clear();
    lastExpression.clear();
}

double CalculatorEngine::getMemory() const {
    return memory;
}

void CalculatorEngine::setMemory(double mem) {
    memory = mem;
}

void CalculatorEngine::addToMemory(double value) {
    memory += value;
}

void CalculatorEngine::subtractFromMemory(double value) {
    memory -= value;
}

double CalculatorEngine::applyRounding(double value) {
    double factor = std::pow(10.0, precision);
    return std::round(value * factor) / factor;
}

std::string CalculatorEngine::getHistory() const {
    return historyManager.getHistory();
}

std::string CalculatorEngine::getLastResult() const {
    return lastResult;
}

std::string CalculatorEngine::getLastExpression() const {
    return lastExpression;
}

void CalculatorEngine::setPrecision(int prec) {
    if (prec > 0 && prec <= 15) {
        precision = prec;
    }
}

int CalculatorEngine::getPrecision() const {
    return precision;
}

bool CalculatorEngine::isValidExpression(const std::string& expression) {
    return parser.parse(expression); // 
}

} // namespace qwencalc
