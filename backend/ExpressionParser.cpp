#include "ExpressionParser.h"
#include <cmath>
#include <cctype>
#include <algorithm>

namespace qwencalc {

ExpressionError::ExpressionError(const std::string& message)
    : std::runtime_error("ExpressionError: " + message) {}

ExpressionParser::ExpressionParser() {}

double ExpressionParser::parse(const std::string& expression) {
    currentExpression = expression;
    
    if (currentExpression.empty()) {
        throw ExpressionError("Empty expression");
    }
    
    int pos = 0;
    double result = parseExpression(pos);
    
    while (isWhitespace(currentExpression[pos])) {
        pos++;
    }
    
    if (pos < currentExpression.length()) {
        throw ExpressionError("Unexpected character in expression at position " + std::to_string(pos));
    }
    
    return result;
}

double ExpressionParser::parseExpression(int& pos) const {
    double left = parseTerm(pos);
    
    while (true) {
        char op = currentExpression[pos];
        if ((op == '+' || op == '-') && isWhitespace(currentExpression[pos + 1])) {
            pos++;
            op = currentExpression[pos];
        }
        
        if (op == '+') {
            pos++;
            while (isWhitespace(currentExpression[pos])) pos++;
            double right = parseTerm(pos);
            left = applyBinaryOperator('+', left, right);
        } else if (op == '-') {
            pos++;
            while (isWhitespace(currentExpression[pos])) pos++;
            double right = parseTerm(pos);
            left = applyBinaryOperator('-', left, right);
        } else {
            break;
        }
    }
    
    return left;
}

double ExpressionParser::parseTerm(int& pos) const {
    double left = parseFactor(pos);
    
    while (true) {
        char op = currentExpression[pos];
        if ((op == '*' || op == '/') && isWhitespace(currentExpression[pos + 1])) {
            pos++;
            op = currentExpression[pos];
        }
        
        if (op == '*') {
            pos++;
            while (isWhitespace(currentExpression[pos])) pos++;
            double right = parseFactor(pos);
            left = applyBinaryOperator('*', left, right);
        } else if (op == '/') {
            pos++;
            while (isWhitespace(currentExpression[pos])) pos++;
            double right = parseFactor(pos);
            left = applyBinaryOperator('/', left, right);
        } else if (op == '%') {
            pos++;
            while (isWhitespace(currentExpression[pos])) pos++;
            double right = parseFactor(pos);
            left = applyBinaryOperator('%', left, right);
        } else {
            break;
        }
    }
    
    return left;
}

double ExpressionParser::parseFactor(int& pos) const {
    if (currentExpression[pos] == '-') {
        pos++;
        return applyUnaryOperator('-', parseFactor(pos));
    } else if (currentExpression[pos] == '+') {
        pos++;
        return parseFactor(pos);
    }
    
    double result = parseNumber(pos);
    
    std::string funcName = "";
    while (isWhitespace(currentExpression[pos])) pos++;
    
    if (pos + 1 < currentExpression.length() && isFunctionChar(currentExpression[pos]) && currentExpression[pos + 1] == '(') {
        int start = pos;
        funcName += currentExpression[pos];
        pos++;
        
        while (pos < currentExpression.length() && currentExpression[pos] != '(') {
            funcName += currentExpression[pos];
            pos++;
            if (isWhitespace(currentExpression[pos])) {
                while (isWhitespace(currentExpression[pos])) pos++;
            }
        }
        
        if (pos < currentExpression.length()) {
            std::string func = funcName;
            while (func.empty() && isFunctionChar(currentExpression[pos])) {
                func += currentExpression[pos];
                pos++;
            }
            
            double arg = parseExpression(pos);
            pos++;
            
            switch (func[0]) {
                case 's':
                    if (func == "sin") result = std::sin(arg);
                    else if (func == "sinh") result = std::sinh(arg);
                    break;
                case 'c':
                    if (func == "cos") result = std::cos(arg);
                    else if (func == "cosh") result = std::cosh(arg);
                    break;
                case 't':
                    if (func == "tan") result = std::tan(arg);
                    else if (func == "tanh") result = std::tanh(arg);
                    break;
                case 'l':
                    if (func == "log") result = std::log10(arg);
                    else if (func == "ln") result = std::log(arg);
                    break;
                case 'r':
                    if (func == "sqrt") result = std::sqrt(arg);
                    break;
                case 'p':
                    if (func == "pow") result = std::pow(arg, 1.0);
                    break;
                case 'f':
                    if (func == "factorial") result = factorial(arg);
                    break;
            }
        }
    }
    
    return result;
}

double ExpressionParser::parseNumber(int& pos) const {
    std::string numberStr;
    
    while (pos < currentExpression.length()) {
        char c = currentExpression[pos];
        if (isdigit(c) || c == '.' || c == '-' || c == '+') {
            numberStr += c;
            pos++;
        } else if (c == 'e' && numberStr.length() > 0) {
            numberStr += c;
            pos++;
            if (pos < currentExpression.length()) {
                numberStr += currentExpression[pos];
                pos++;
            }
        } else {
            break;
        }
    }
    
    return std::stod(numberStr);
}

double ExpressionParser::applyUnaryOperator(char op, double value) const {
    if (op == '-') {
        return -value;
    }
    throw ExpressionError("Invalid unary operator");
}

double ExpressionParser::applyBinaryOperator(char op, double left, double right) const {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/':
            if (right == 0.0) {
                throw ExpressionError("Division by zero");
            }
            return left / right;
        case '%':
            if (right == 0.0) {
                throw ExpressionError("Modulo by zero");
            }
            return std::fmod(left, right);
        default:
            throw ExpressionError("Invalid operator");
    }
}

double ExpressionParser::factorial(int n) {
    if (n < 0) {
        throw ExpressionError("Factorial of negative number");
    }
    if (n > 170) {
        throw ExpressionError("Factorial overflow");
    }
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double ExpressionParser::factorial(double n) {
    if (n < 0) {
        throw ExpressionError("Factorial of negative number");
    }
    return factorialHelper(n);
}

double ExpressionParser::factorialHelper(double n) {
    double result = 1.0;
    for (double i = 2.0; i <= n; i++) {
        result *= i;
    }
    return result;
}

bool ExpressionParser::isOperatorChar(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

bool ExpressionParser::isUnaryOperator(char c) const {
    return c == '+' || c == '-';
}

bool ExpressionParser::isFactorOperator(char c) const {
    return c == '+' || c == '-';
}

bool ExpressionParser::isNumberChar(char c) const {
    return isdigit(c);
}

bool ExpressionParser::isFunctionChar(char c) const {
    return isalpha(c);
}

bool ExpressionParser::hasFunction(const std::string& expression, const std::string& funcName) const {
    size_t found = expression.find(funcName);
    return found != std::string::npos;
}

bool ExpressionParser::isParenthesis(char c) const {
    return c == '(' || c == ')';
}

bool ExpressionParser::isWhitespace(char c) const {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

void ExpressionParser::tokenize(const std::string& expression, std::vector<char>& tokens, std::vector<std::string>& values) {
}

} // namespace qwencalc
