#include <gtest/gtest.h>
#include "ExpressionParser.h"
#include <cmath>

using namespace qwencalc;

class ExpressionParserTest : public testing::Test {
protected:
    ExpressionParser parser;
};

TEST_F(ExpressionParserTest, BasicAddition) {
    EXPECT_DOUBLE_EQ(parser.parse("1 + 2"), 3.0);
    EXPECT_DOUBLE_EQ(parser.parse("10 + 20"), 30.0);
    EXPECT_DOUBLE_EQ(parser.parse("100.5 + 0.5"), 101.0);
}

TEST_F(ExpressionParserTest, BasicSubtraction) {
    EXPECT_DOUBLE_EQ(parser.parse("5 - 3"), 2.0);
    EXPECT_DOUBLE_EQ(parser.parse("10 - 20"), -10.0);
    EXPECT_DOUBLE_EQ(parser.parse("3.5 - 1.5"), 2.0);
}

TEST_F(ExpressionParserTest, BasicMultiplication) {
    EXPECT_DOUBLE_EQ(parser.parse("4 * 5"), 20.0);
    EXPECT_DOUBLE_EQ(parser.parse("3.0 * 2.0"), 6.0);
}

TEST_F(ExpressionParserTest, BasicDivision) {
    EXPECT_DOUBLE_EQ(parser.parse("10 / 2"), 5.0);
    EXPECT_DOUBLE_EQ(parser.parse("7.0 / 2.0"), 3.5);
    EXPECT_DOUBLE_EQ(parser.parse("100.0 / 4.0"), 25.0);
}

TEST_F(ExpressionParserTest, MixedOperations) {
    EXPECT_DOUBLE_EQ(parser.parse("2 + 3 * 4"), 14.0);
    EXPECT_DOUBLE_EQ(parser.parse("(2 + 3) * 4"), 20.0);
    EXPECT_DOUBLE_EQ(parser.parse("10 / 2 + 3"), 8.0);
}

TEST_F(ExpressionParserTest, DivisionByZero) {
    EXPECT_THROW(parser.parse("10 / 0"), ExpressionError);
    EXPECT_THROW(parser.parse("5 / 0.0"), ExpressionError);
}

TEST_F(ExpressionParserTest, Modulo) {
    EXPECT_DOUBLE_EQ(parser.parse("10 % 3"), 1.0);
    EXPECT_DOUBLE_EQ(parser.parse("5 % 2"), 1.0);
    EXPECT_THROW(parser.parse("10 % 0"), ExpressionError);
}

TEST_F(ExpressionParserTest, TrigonometricFunctions) {
    EXPECT_NEAR(parser.parse("sin(0)"), 0.0, 1e-10);
    EXPECT_NEAR(parser.parse("sin(M_PI/2)"), 1.0, 1e-10);
    EXPECT_NEAR(parser.parse("cos(0)"), 1.0, 1e-10);
    EXPECT_NEAR(parser.parse("cos(0)"), 1.0, 1e-10);
    EXPECT_NEAR(parser.parse("tan(M_PI/4)"), 1.0, 1e-10);
}

TEST_F(ExpressionParserTest, Logarithm) {
    EXPECT_NEAR(parser.parse("log(10)"), 1.0, 1e-10);
    EXPECT_NEAR(parser.parse("ln(e)"), 1.0, 1e-10);
}

TEST_F(ExpressionParserTest, SquareRoot) {
    EXPECT_DOUBLE_EQ(parser.parse("sqrt(4)"), 2.0);
    EXPECT_DOUBLE_EQ(parser.parse("sqrt(16)"), 4.0);
}

TEST_F(ExpressionParserTest, Power) {
    EXPECT_DOUBLE_EQ(parser.parse("pow(2,3)"), 8.0);
    EXPECT_DOUBLE_EQ(parser.parse("pow(10,2)"), 100.0);
}

TEST_F(ExpressionParserTest, Factorial) {
    EXPECT_DOUBLE_EQ(parser.parse("factorial(5)"), 120.0);
    EXPECT_DOUBLE_EQ(parser.parse("factorial(0)"), 1.0);
    EXPECT_THROW(parser.parse("factorial(-1)"), ExpressionError);
}

TEST_F(ExpressionParserTest, Parentheses) {
    EXPECT_DOUBLE_EQ(parser.parse("(2 + 3) * 4"), 20.0);
    EXPECT_DOUBLE_EQ(parser.parse("((1 + 2) * 3)"), 9.0);
    EXPECT_DOUBLE_EQ(parser.parse("10 - (2 + 3)"), 5.0);
}

TEST_F(ExpressionParserTest, NegativeNumbers) {
    EXPECT_DOUBLE_EQ(parser.parse("-5 + 3"), -2.0);
    EXPECT_DOUBLE_EQ(parser.parse("5 - -3"), 8.0);
    EXPECT_DOUBLE_EQ(parser.parse("--5"), 5.0);
}

TEST_F(ExpressionParserTest, UnaryOperators) {
    EXPECT_DOUBLE_EQ(parser.parse("+5"), 5.0);
    EXPECT_DOUBLE_EQ(parser.parse("-5"), -5.0);
}

TEST_F(ExpressionParserTest, ScientificNotation) {
    EXPECT_DOUBLE_EQ(parser.parse("1e2"), 100.0);
    EXPECT_DOUBLE_EQ(parser.parse("1.5e3"), 1500.0);
}

TEST_F(ExpressionParserTest, ComplexExpression) {
    EXPECT_DOUBLE_EQ(parser.parse("sin(PI/2) + cos(0)"), 2.0);
    EXPECT_DOUBLE_EQ(parser.parse("2 * (3 + 4) / 2"), 7.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
