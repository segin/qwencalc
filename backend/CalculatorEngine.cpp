#include "CalculatorEngine.h"
#include <cmath>

namespace qwencalc {

CalculatorEngine::CalculatorEngine()
    : memory(0.0), precision(10) {}

double CalculatorEngine::calculate(const std::string& expression) {
    try {
        double result = parser.parse(expression);
        result = applyRounding(result);
        
        lastResult = std::to_string(result);
        lastExpression = expression;
        
        historyManager.addEntry(expression, result);
        
        return result;
    } catch (const ExpressionError& e) {
        lastResult = "Error";
        throw;
    }
}

void CalculatorEngine::clear() {
    memory = 0.0;
    lastResult.clear();
    lastExpression.clear();
}

void CalculatorEngine::clearHistory() {
    historyManager.clear();
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

void CalculatorEngine::recallMemory() {
    lastResult = std::to_string(memory);
}

void CalculatorEngine::storeMemory(const std::string& expression) {
    double result = parser.parse(expression);
    memory = result;
    lastResult = std::to_string(memory);
    lastExpression = expression;
    historyManager.addEntry(expression, memory);
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
    precision = std::max(1, std::min(20, prec));
}

int CalculatorEngine::getPrecision() const {
    return precision;
}

bool CalculatorEngine::isValidExpression(const std::string& expression) const {
    if (expression.empty()) {
        return false;
    }
    
    bool valid = true;
    try {
        double result = parser.parse(expression);
    } catch (...) {
        valid = false;
    }
    
    return valid;
}

double CalculatorEngine::applyRounding(double value) {
    double multiplier = std::pow(10.0, precision);
    return std::round(value * multiplier) / multiplier;
}

} // namespace qwencalc
