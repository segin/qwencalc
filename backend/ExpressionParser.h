#pragma once

#include <stdexcept>
#include <string>
#include <vector>

/**
 * ExpressionError exception class for handling parsing errors.
 * Thrown when expressions contain invalid syntax or operations.
 */
namespace qwencalc {

class ExpressionError : public std::runtime_error {
  public:
    explicit ExpressionError(const std::string &message)
        : std::runtime_error(message) {}
};

/**
 * ExpressionParser class for parsing and evaluating mathematical expressions.
 * Supports basic arithmetic operations, trigonometric functions, logarithms,
 * and more.
 * @throws ExpressionError when parsing fails due to invalid input
 */
class ExpressionParser {
  public:
    ExpressionParser();

    /**
     * Parse and evaluate the given mathematical expression.
     * @param expression The mathematical expression string to parse
     * @return The result of the expression evaluation
     * @throws ExpressionError if the expression is invalid
     */
    double parse(const std::string &expression);

  private:
    std::string currentExpression;

    /**
     * Parse expression level (addition/subtraction)
     * @param pos Reference to current position in expression
     * @return The parsed expression value
     */
    double parseExpression(int &pos) const;

    /**
     * Parse term level (multiplication/division)
     * @param pos Reference to current position in expression
     * @return The parsed term value
     */
    double parseTerm(int &pos) const;

    /**
     * Parse factor level (unary operators, parentheses, function calls)
     * @param pos Reference to current position in expression
     * @return The parsed factor value
     */
    double parseFactor(int &pos) const;

    /**
     * Parse a number including scientific notation
     * @param pos Reference to current position in expression
     * @return The parsed number value
     */
    double parseNumber(int &pos) const;

    /**
     * Apply unary operator to value.
     * @param op The unary operator character ('!' for factorial, '-' for
     * negation)
     * @param value The value to apply the operator to
     * @return The result after applying the unary operator
     * @throws ExpressionError for invalid factorial inputs
     */
    double applyUnaryOperator(char op, double value) const;

    void skipWhitespace(int &pos) const;
};

} // namespace qwencalc