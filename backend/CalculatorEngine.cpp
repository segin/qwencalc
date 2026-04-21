#include "CalculatorEngine.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace qwencalc {

CalculatorEngine::CalculatorEngine() : memory(0.0), precision(10) {}

double CalculatorEngine::calculate(const std::string &expression) {
    double result = 0.0;

    result = parser.parse(expression);
    result = applyRounding(result);
    lastResult = formatResult(result);
    lastExpression = expression;

    historyManager.addEntry(expression, result);
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

double CalculatorEngine::getMemory() const { return memory; }

void CalculatorEngine::setMemory(double mem) { memory = mem; }

void CalculatorEngine::addToMemory(double value) { memory += value; }

void CalculatorEngine::subtractFromMemory(double value) { memory -= value; }

double CalculatorEngine::applyRounding(double value) {
    double factor = std::pow(10.0, precision);
    return std::round(value * factor) / factor;
}

std::string CalculatorEngine::getHistory() const {
    return historyManager.getHistory();
}

std::string CalculatorEngine::getLastResult() const { return lastResult; }

std::string CalculatorEngine::formatResult(double value) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;

    std::string result = ss.str();

    std::string trimmed = result;
    while (trimmed.size() > 1 && trimmed.back() == '0') {
        trimmed.pop_back();
    }
    if (trimmed.size() > 1 && trimmed.back() == '.') {
        trimmed.pop_back();
    }

    return trimmed;
}

std::string CalculatorEngine::getLastExpression() const {
    return lastExpression;
}

void CalculatorEngine::setPrecision(int prec) {
    if (prec > 0 && prec <= 15) {
        precision = prec;
    }
}

int CalculatorEngine::getPrecision() const { return precision; }

bool CalculatorEngine::isValidExpression(const std::string &expression) {
    try {
        parser.parse(expression);
        return true;
    } catch (const ExpressionError &) {
        return false;
    }
}

void CalculatorEngine::storeMemory(const std::string &expression) {
    try {
        double result = parser.parse(expression);
        memory = result;
    } catch (const ExpressionError &) {
        memory = 0.0;
    }
}

} // namespace qwencalc
