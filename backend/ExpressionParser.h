#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>

namespace qwencalc {

class ExpressionError : public std::runtime_error {
public:
    explicit ExpressionError(const std::string& message);
};

class ExpressionParser {
public:
    ExpressionParser();
    
    double parse(const std::string& expression) const;
    
    double parseExpression(int& pos) const;
    double parseTerm(int& pos) const;
    double parseFactor(int& pos) const;
    double parseNumber(int& pos) const;
    
    double applyUnaryOperator(char op, double value) const;
    double applyBinaryOperator(char op, double left, double right) const;
    
    double factorial(int n);
    double factorial(double n);
    
    bool isOperatorChar(char c) const;
    bool isUnaryOperator(char c) const;
    bool isFactorOperator(char c) const;
    bool isNumberChar(char c) const;
    bool isFunctionChar(char c) const;
    
    bool hasFunction(const std::string& expression, const std::string& funcName) const;
    bool isParenthesis(char c) const;
    bool isWhitespace(char c) const;
    
    double factorialHelper(double n);
    
    void tokenize(const std::string& expression, std::vector<char>& tokens, std::vector<std::string>& values);
    
private:
    std::string currentExpression;
};

} // namespace qwencalc

#endif // EXPRESSION_PARSER_H
