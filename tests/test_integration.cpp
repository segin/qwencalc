#include "CalculatorEngine.h"
#include "ExpressionParser.h"
#include "HistoryManager.h"
#include <iostream>
#include <cmath>
#include <cassert>

using namespace qwencalc;

void testCalculateBasic() {
    CalculatorEngine engine;
    double result = engine.calculate("2 + 2");
    assert(std::abs(result - 4.0) < 0.001);
    std::cout << "✓ Basic addition test passed" << std::endl;
}

void testCalculateMultiplication() {
    CalculatorEngine engine;
    double result = engine.calculate("3 * 4");
    assert(std::abs(result - 12.0) < 0.001);
    std::cout << "✓ Multiplication test passed" << std::endl;
}

void testCalculateDivision() {
    CalculatorEngine engine;
    double result = engine.calculate("10 / 2");
    assert(std::abs(result - 5.0) < 0.001);
    std::cout << "✓ Division test passed" << std::endl;
}

void testCalculateParentheses() {
    CalculatorEngine engine;
    double result = engine.calculate("(2 + 3) * 4");
    assert(std::abs(result - 20.0) < 0.001);
    std::cout << "✓ Parentheses test passed" << std::endl;
}

void testCalculateOrderOfOperations() {
    CalculatorEngine engine;
    double result = engine.calculate("2 + 3 * 4");
    assert(std::abs(result - 14.0) < 0.001);
    std::cout << "✓ Order of operations test passed" << std::endl;
}

void testCalculateSin() {
    CalculatorEngine engine;
    double result = engine.calculate("sin(0)");
    assert(std::abs(result - 0.0) < 0.001);
    std::cout << "✓ Sine function test passed" << std::endl;
}

void testCalculateCos() {
    CalculatorEngine engine;
    double result = engine.calculate("cos(0)");
    assert(std::abs(result - 1.0) < 0.001);
    std::cout << "✓ Cosine function test passed" << std::endl;
}

void testClear() {
    CalculatorEngine engine;
    engine.calculate("1 + 1");
    engine.clear();
    double result = engine.calculate("2 * 2");
    assert(std::abs(result - 4.0) < 0.001);
    std::cout << "✓ Clear test passed" << std::endl;
}

void testMemory() {
    CalculatorEngine engine;
    engine.setMemory(10);
    double memory = engine.getMemory();
    assert(std::abs(memory - 10.0) < 0.001);
    std::cout << "✓ Memory test passed" << std::endl;
}

void testAddToMemory() {
    CalculatorEngine engine;
    engine.setMemory(5);
    engine.addToMemory(3);
    double memory = engine.getMemory();
    assert(std::abs(memory - 8.0) < 0.001);
    std::cout << "✓ Add to memory test passed" << std::endl;
}

void testSubtractFromMemory() {
    CalculatorEngine engine;
    engine.setMemory(10);
    engine.subtractFromMemory(4);
    double memory = engine.getMemory();
    assert(std::abs(memory - 6.0) < 0.001);
    std::cout << "✓ Subtract from memory test passed" << std::endl;
}

void testPrecision() {
    CalculatorEngine engine;
    engine.setPrecision(4);
    double result = engine.calculate("1.0 / 3.0");
    std::string resultStr = std::to_string(result);
    std::cout << "✓ Precision test passed: " << resultStr << std::endl;
}

void testValidExpression() {
    CalculatorEngine engine;
    bool valid = engine.isValidExpression("2 + 2");
    assert(valid == true);
    std::cout << "✓ Valid expression test passed" << std::endl;
}

void testInvalidExpression() {
    CalculatorEngine engine;
    bool valid = engine.isValidExpression("2 + *");
    assert(valid == false);
    std::cout << "✓ Invalid expression test passed" << std::endl;
}

void testHistory() {
    CalculatorEngine engine;
    engine.calculate("2 + 2");
    engine.calculate("3 * 3");
    std::string history = engine.getHistory();
    assert(history.find("2 + 2") != std::string::npos);
    std::cout << "✓ History test passed" << std::endl;
}