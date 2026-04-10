#ifndef CALCULATOR_ENGINE_H
#define CALCULATOR_ENGINE_H

#include "ExpressionParser.h"
#include "HistoryManager.h"
#include <string>

namespace qwencalc {

class CalculatorEngine {
public:
    CalculatorEngine();
    
    double calculate(const std::string& expression);
    
    void clear();
    void clearHistory();
    
    double getMemory() const;
    void setMemory(double memory);
    
    void addToMemory(double value);
    void subtractFromMemory(double value);
    void recallMemory();
    void storeMemory(const std::string& expression);
    
    std::string getHistory() const;
    std::string getLastResult() const;
    std::string getLastExpression() const;
    
    void setPrecision(int precision);
    int getPrecision() const;
    
    bool isValidExpression(const std::string& expression);
    
private:
    ExpressionParser parser;
    HistoryManager historyManager;
    double memory;
    int precision;
    std::string lastResult;
    std::string lastExpression;
    
    double applyRounding(double value);
};

} // namespace qwencalc

#endif // CALCULATOR_ENGINE_H
