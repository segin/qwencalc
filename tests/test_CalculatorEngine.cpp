#include <gtest/gtest.h>
#include "../backend/CalculatorEngine.h"

using namespace qwencalc;

class CalculatorEngineTest : public ::testing::Test {
protected:
    CalculatorEngine engine;
};

TEST_F(CalculatorEngineTest, Addition) {
    double result = engine.calculate("2 + 2");
    EXPECT_DOUBLE_EQ(result, 4.0);
}

TEST_F(CalculatorEngineTest, Subtraction) {
    double result = engine.calculate("10 - 5");
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(CalculatorEngineTest, Multiplication) {
    double result = engine.calculate("3 * 4");
    EXPECT_DOUBLE_EQ(result, 12.0);
}

TEST_F(CalculatorEngineTest, Division) {
    double result = engine.calculate("10 / 2");
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(CalculatorEngineTest, ComplexExpression) {
    double result = engine.calculate("(2 + 3) * 4");
    EXPECT_DOUBLE_EQ(result, 20.0);
}

TEST_F(CalculatorEngineTest, DivisionByZero) {
    EXPECT_THROW(engine.calculate("5 / 0"), qwencalc::ExpressionError);
}

TEST_F(CalculatorEngineTest, InvalidExpression) {
    try {
        engine.calculate("abc + def");
    } catch (const qwencalc::ExpressionError&) {
        return; // Expected
    }
    FAIL() << "Expected ExpressionError for invalid expression";
}

TEST_F(CalculatorEngineTest, GetLastResult) {
    engine.calculate("5 + 5");
    EXPECT_NE(engine.getLastResult(), "");
}

TEST_F(CalculatorEngineTest, GetLastExpression) {
    engine.calculate("8 * 2");
    EXPECT_EQ(engine.getLastExpression(), "8 * 2");
}

TEST_F(CalculatorEngineTest, Clear) {
    engine.setMemory(10.0);
    engine.calculate("3 + 3");
    engine.clear();
    EXPECT_DOUBLE_EQ(engine.getMemory(), 0.0);
}

TEST_F(CalculatorEngineTest, ClearHistory) {
    engine.calculate("1 + 1");
    engine.calculate("2 + 2");
    engine.clearHistory();
    EXPECT_EQ(engine.getLastResult(), "");
}

TEST_F(CalculatorEngineTest, Memory) {
    engine.setMemory(100.0);
    EXPECT_DOUBLE_EQ(engine.getMemory(), 100.0);
    
    engine.addToMemory(50.0);
    EXPECT_DOUBLE_EQ(engine.getMemory(), 150.0);
    
    engine.subtractFromMemory(25.0);
    EXPECT_DOUBLE_EQ(engine.getMemory(), 125.0);
}

TEST_F(CalculatorEngineTest, Precision) {
    engine.setPrecision(4);
    EXPECT_EQ(engine.getPrecision(), 4);
}

TEST_F(CalculatorEngineTest, ValidExpression) {
    EXPECT_TRUE(engine.isValidExpression("3 + 4"));
    EXPECT_FALSE(engine.isValidExpression("abc + def"));
}

