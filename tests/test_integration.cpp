#define _USE_MATH_DEFINES
#include "CalculatorEngine.h"
#include "ExpressionParser.h"
#include "HistoryManager.h"
#include <cmath>
#include <gtest/gtest.h>

using namespace qwencalc;

// Basic arithmetic tests

TEST(TestIntegration, testCalculateBasic) {
    CalculatorEngine engine;
    double result = engine.calculate("2 + 2");
    EXPECT_NEAR(result, 4.0, 0.001);
}

TEST(TestIntegration, testCalculateMultiplication) {
    CalculatorEngine engine;
    double result = engine.calculate("3 * 4");
    EXPECT_NEAR(result, 12.0, 0.001);
}

TEST(TestIntegration, testCalculateDivision) {
    CalculatorEngine engine;
    double result = engine.calculate("10 / 2");
    EXPECT_NEAR(result, 5.0, 0.001);
}

TEST(TestIntegration, testCalculateModulo) {
    CalculatorEngine engine;
    double result = engine.calculate("10 % 3");
    EXPECT_NEAR(result, 1.0, 0.001);
}

// Parentheses and order of operations

TEST(TestIntegration, testCalculateParentheses) {
    CalculatorEngine engine;
    double result = engine.calculate("(2 + 3) * 4");
    EXPECT_NEAR(result, 20.0, 0.001);
}

TEST(TestIntegration, testCalculateOrderOfOperations) {
    CalculatorEngine engine;
    double result = engine.calculate("2 + 3 * 4");
    EXPECT_NEAR(result, 14.0, 0.001);
}

// Trigonometric functions (degrees)

TEST(TestIntegration, testCalculateSin) {
    CalculatorEngine engine;
    double result = engine.calculate("sin(0)");
    EXPECT_NEAR(result, 0.0, 0.001);
}

TEST(TestIntegration, testCalculateCos) {
    CalculatorEngine engine;
    double result = engine.calculate("cos(0)");
    EXPECT_NEAR(result, 1.0, 0.001);
}

TEST(TestIntegration, testCalculateTan) {
    CalculatorEngine engine;
    double result = engine.calculate("tan(45)");
    double expected = std::tan(45.0 * M_PI / 180.0);
    EXPECT_NEAR(result, expected, 0.001);
}

TEST(TestIntegration, testCalculateSin90) {
    CalculatorEngine engine;
    double result = engine.calculate("sin(90)");
    double expected = std::sin(90.0 * M_PI / 180.0);
    EXPECT_NEAR(result, expected, 0.001);
}

// Power function

TEST(TestIntegration, testCalculatePower) {
    CalculatorEngine engine;
    double result = engine.calculate("2 ^ 8");
    EXPECT_NEAR(result, 256.0, 0.001);
}

// Logarithmic functions

TEST(TestIntegration, testCalculateLog10) {
    CalculatorEngine engine;
    double result = engine.calculate("log(100)");
    EXPECT_NEAR(result, 2.0, 0.001);
}

TEST(TestIntegration, testCalculateLn) {
    CalculatorEngine engine;
    double result = engine.calculate("ln(2.7182818)");
    EXPECT_NEAR(result, 1.0, 0.01);
}

// Square root

TEST(TestIntegration, testCalculateSqrt) {
    CalculatorEngine engine;
    double result = engine.calculate("sqrt(16)");
    EXPECT_NEAR(result, 4.0, 0.001);
}

// Factorial

TEST(TestIntegration, testCalculateFactorial) {
    CalculatorEngine engine;
    double result = engine.calculate("5!");
    EXPECT_NEAR(result, 120.0, 0.001);
}

// Clear and reset

TEST(TestIntegration, testClear) {
    CalculatorEngine engine;
    engine.calculate("1 + 1");
    engine.clear();
    double result = engine.calculate("2 * 2");
    EXPECT_NEAR(result, 4.0, 0.001);
}

// Memory operations

TEST(TestIntegration, testMemory) {
    CalculatorEngine engine;
    engine.setMemory(10);
    double memory = engine.getMemory();
    EXPECT_NEAR(memory, 10.0, 0.001);
}

TEST(TestIntegration, testAddToMemory) {
    CalculatorEngine engine;
    engine.setMemory(5);
    engine.addToMemory(3);
    double memory = engine.getMemory();
    EXPECT_NEAR(memory, 8.0, 0.001);
}

TEST(TestIntegration, testSubtractFromMemory) {
    CalculatorEngine engine;
    engine.setMemory(10);
    engine.subtractFromMemory(4);
    double memory = engine.getMemory();
    EXPECT_NEAR(memory, 6.0, 0.001);
}

TEST(TestIntegration, testRecallMemory) {
    CalculatorEngine engine;
    engine.setMemory(42);
    double mem = engine.getMemory();
    EXPECT_NEAR(mem, 42.0, 0.001);
}

// Precision handling

TEST(TestIntegration, testPrecision) {
    CalculatorEngine engine;
    engine.setPrecision(4);
    double result = engine.calculate("1.0 / 3.0");
    std::string resultStr = std::to_string(result);
    // Just verify it doesn't crash and produces a reasonable result
    EXPECT_GT(result, 0.0);
}

// Expression validation

TEST(TestIntegration, testValidExpression) {
    CalculatorEngine engine;
    bool valid = engine.isValidExpression("2 + 2");
    EXPECT_TRUE(valid);
}

TEST(TestIntegration, testInvalidExpression) {
    CalculatorEngine engine;
    bool valid = engine.isValidExpression("2 + *");
    EXPECT_FALSE(valid);
}

TEST(TestIntegration, testInvalidExpressionEmpty) {
    CalculatorEngine engine;
    bool valid = engine.isValidExpression("");
    EXPECT_FALSE(valid);
}

// History tracking

TEST(TestIntegration, testHistory) {
    CalculatorEngine engine;
    engine.calculate("2 + 2");
    engine.calculate("3 * 3");
    std::string history = engine.getHistory();
    EXPECT_NE(history.find("2 + 2"), std::string::npos);
}

TEST(TestIntegration, testHistoryContainsResult) {
    CalculatorEngine engine;
    engine.calculate("10 + 5");
    std::string history = engine.getHistory();
    EXPECT_NE(history.find("15"), std::string::npos);
}

// Complex expressions

TEST(TestIntegration, testComplexExpression) {
    CalculatorEngine engine;
    double result = engine.calculate("(2 + 3) * (4 - 1)");
    EXPECT_NEAR(result, 15.0, 0.001);
}

TEST(TestIntegration, testNestedParentheses) {
    CalculatorEngine engine;
    double result = engine.calculate("((2 + 3) * 4) - 5");
    EXPECT_NEAR(result, 15.0, 0.001);
}

TEST(TestIntegration, testExpressionWithSin) {
    CalculatorEngine engine;
    double result = engine.calculate("sin(30) + 1");
    double expected = std::sin(30.0 * M_PI / 180.0) + 1.0;
    EXPECT_NEAR(result, expected, 0.001);
}

TEST(TestIntegration, testExpressionWithLog) {
    CalculatorEngine engine;
    double result = engine.calculate("log(1000)");
    EXPECT_NEAR(result, 3.0, 0.001);
}

TEST(TestIntegration, testExpressionWithFactorial) {
    CalculatorEngine engine;
    double result = engine.calculate("sqrt(9) + 3!");
    double expected = std::sqrt(9.0) + 6.0; // 3! = 6
    EXPECT_NEAR(result, expected, 0.001);
}

TEST(TestIntegration, testExpressionWithPowerAndSin) {
    CalculatorEngine engine;
    double result = engine.calculate("2 ^ 4 + sin(0)");
    EXPECT_NEAR(result, 16.0, 0.001);
}

TEST(TestIntegration, testNegativeNumbers) {
    CalculatorEngine engine;
    double result = engine.calculate("-5 + 3");
    EXPECT_NEAR(result, -2.0, 0.001);
}

TEST(TestIntegration, testDecimalCalculation) {
    CalculatorEngine engine;
    double result = engine.calculate("1.5 + 2.5");
    EXPECT_NEAR(result, 4.0, 0.001);
}

TEST(TestIntegration, testMultipleOperators) {
    CalculatorEngine engine;
    double result = engine.calculate("10 / 2 / 5");
    EXPECT_NEAR(result, 1.0, 0.001);
}
