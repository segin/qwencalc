#define _USE_MATH_DEFINES
#include "ExpressionParser.h"
#include <cmath>
#include <cctype>
#include <string>

namespace qwencalc {

namespace {

std::string toLower(const std::string& str) {
    std::string result = str;
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = std::tolower(static_cast<unsigned char>(result[i]));
    }
    return result;
}

bool isWordBoundary(const std::string& str, int pos) {
    return pos >= (int)str.length() || !std::isalnum(static_cast<unsigned char>(str[pos]));
}

} // namespace

ExpressionParser::ExpressionParser() {}

void ExpressionParser::skipWhitespace(int& pos) const {
    while (pos < (int)currentExpression.length() && 
           std::isspace(currentExpression[pos])) {
        pos++;
    }
}

double ExpressionParser::parse(const std::string& expression) {
    currentExpression = expression;
    
    int pos = 0;
    skipWhitespace(pos);
    double result = parseExpression(pos);
    
    if (pos < (int)currentExpression.length()) {
        throw ExpressionError("Unexpected characters at end");
    }
    
    return result;
}

double ExpressionParser::parseExpression(int& pos) const {
    skipWhitespace(pos);
    double left = parseTerm(pos);
    
    while (pos < (int)currentExpression.length()) {
        skipWhitespace(pos);
        if (pos >= (int)currentExpression.length()) break;
        
        char c = currentExpression[pos];
        
        if (c == '+' || c == '-') {
            pos++;
            double right = parseTerm(pos);
            left = (c == '+') ? (left + right) : (left - right);
        } else {
            break;
        }
    }
    
    return left;
}

double ExpressionParser::parseTerm(int& pos) const {
    skipWhitespace(pos);
    double left = parseFactor(pos);
    
    while (pos < (int)currentExpression.length()) {
        skipWhitespace(pos);
        if (pos >= (int)currentExpression.length()) break;
        
        char c = currentExpression[pos];
        
        if (c == '*' || c == '/' || c == '%' || c == '^') {
            pos++;
            skipWhitespace(pos);
            if (pos >= (int)currentExpression.length()) {
                break;
            }
            double right = parseFactor(pos);
            if (c == '*') {
                left = left * right;
            } else if (c == '/') {
                if (right == 0) {
                    throw ExpressionError("Division by zero");
                }
                left = left / right;
            } else if (c == '%') {
                if (right == 0) {
                    throw ExpressionError("Modulo by zero");
                }
                left = std::fmod(left, right);
            } else if (c == '^') {
                left = std::pow(left, right);
            }
        } else {
            break;
        }
    }
    
    return left;
}

double ExpressionParser::parseNumber(int& pos) const {
    skipWhitespace(pos);
    
    if (pos + 2 <= (int)currentExpression.length()) {
        std::string substr2 = currentExpression.substr(pos, 2);
        std::string substr2Lower = toLower(substr2);
        if (substr2Lower == "pi" && isWordBoundary(currentExpression, pos + 2)) {
            pos += 2;
            return M_PI;
        }
    }
    
    if (pos + 4 <= (int)currentExpression.length()) {
        std::string substr4 = currentExpression.substr(pos, 4);
        std::string substr4Lower = toLower(substr4);
        if (substr4Lower == "m_pi" && isWordBoundary(currentExpression, pos + 4)) {
            pos += 4;
            return M_PI;
        }
    }
    
    if (pos < (int)currentExpression.length()) {
        std::string charStr = currentExpression.substr(pos, 1);
        if ((charStr == "e" || charStr == "E") && isWordBoundary(currentExpression, pos + 1)) {
            pos++;
            return M_E;
        }
    }
    
    // Track position before parsing digits
    int startpos = pos;
    
    double value = 0.0;
    bool hasDecimal = false;
    int decimalDigits = 0;
    
    while (pos < (int)currentExpression.length()) {
        char c = currentExpression[pos];
        
        if (std::isdigit(c)) {
            if (!hasDecimal) {
                value = value * 10.0 + (c - '0');
            } else {
                decimalDigits++;
                value += (c - '0') * std::pow(10.0, -decimalDigits);
            }
            pos++;
        } else if (c == '.' && !hasDecimal) {
            hasDecimal = true;
            pos++;
        } else if (c == 'e' || c == 'E') {
            break;
        } else {
            break;
        }
    }
    
    // Check for scientific notation (e or E followed by digits, with optional sign)
    while (pos < (int)currentExpression.length() && (currentExpression[pos] == 'e' || currentExpression[pos] == 'E')) {
        pos++;
        skipWhitespace(pos);
        
        bool isNegative = false;
        if (pos < (int)currentExpression.length()) {
            char expChar = currentExpression[pos];
            if (expChar == '+' || expChar == '-') {
                isNegative = (expChar == '-');
                pos++;
            }
        }
        
        // Read exponent digits
        int exponentValue = 0;
        bool readDigits = false;
        while (pos < (int)currentExpression.length() && std::isdigit(currentExpression[pos])) {
            exponentValue = exponentValue * 10 + (currentExpression[pos] - '0');
            readDigits = true;
            pos++;
        }
        
        if (readDigits) {
            if (isNegative) {
                exponentValue = -exponentValue;
            }
            
            double exponent = 1.0;
            int absExponent = std::abs(exponentValue);
            for (int i = 0; i < absExponent; i++) {
                if (exponentValue < 0) {
                    exponent /= 10.0;
                } else {
                    exponent *= 10.0;
                }
            }
            value *= exponent;
        }
        
        break;
    }
    
    // If we didn't parse anything, throw an error
    if (startpos == pos) {
        throw ExpressionError("Invalid expression");
    }
    
    return value;
}

double ExpressionParser::parseFactor(int& pos) const {
    skipWhitespace(pos);
    
    if (pos >= (int)currentExpression.length()) {
        throw ExpressionError("Unexpected end of expression");
    }
    
    double value = 0.0;
    bool hasValue = false;
    
    // Check for factorial prefix first (for "!-1" case)
    if (currentExpression[pos] == '!') {
        pos++;
        skipWhitespace(pos);
        if (pos >= (int)currentExpression.length()) {
            throw ExpressionError("Invalid expression");
        }
        
        // Parse what comes after the factorial operator
        double operandValue;
        if (currentExpression[pos] == '-') {
            int signCount = 0;
            while (pos < (int)currentExpression.length() && 
                   (currentExpression[pos] == '-' || currentExpression[pos] == '+')) {
                if (currentExpression[pos] == '-') {
                    signCount++;
                }
                pos++;
            }
            skipWhitespace(pos);
            operandValue = parseNumber(pos);
            if (signCount % 2 == 1) {
                operandValue = -operandValue;
            }
        } else if (currentExpression[pos] == '+') {
            int signCount = 0;
            while (pos < (int)currentExpression.length() && 
                   (currentExpression[pos] == '-' || currentExpression[pos] == '+')) {
                if (currentExpression[pos] == '-') {
                    signCount++;
                }
                pos++;
            }
            skipWhitespace(pos);
            operandValue = parseNumber(pos);
        } else {
            operandValue = parseNumber(pos);
        }
        
        int n = static_cast<int>(operandValue);
        if (n < 0) {
            throw ExpressionError("Factorial of negative number");
        }
        if (n > 170) {
            throw ExpressionError("Factorial out of range");
        }
        double result = 1.0;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        value = result;
        hasValue = true;
    } else if (currentExpression[pos] == '(') {
        pos++;
        value = parseExpression(pos);
        skipWhitespace(pos);
        if (pos >= (int)currentExpression.length() || currentExpression[pos] != ')') {
            throw ExpressionError("Expected ')' after expression");
        }
        pos++;
        hasValue = true;
    } else if (currentExpression[pos] == '-' || currentExpression[pos] == '+') {
        int signCount = 0;
        while (pos < (int)currentExpression.length() && 
               (currentExpression[pos] == '-' || currentExpression[pos] == '+')) {
            if (currentExpression[pos] == '-') {
                signCount++;
            }
            pos++;
        }
        skipWhitespace(pos);
        if (currentExpression[pos] == '(') {
            value = parseExpression(pos);
        } else {
            value = parseNumber(pos);
        }
        if (signCount % 2 == 1) {
            value = -value;
        }
        hasValue = true;
    } else {
        // Check for function name
        std::string func;
        bool isFunction = false;
        std::string remaining = currentExpression.substr(pos);
        std::string remainingLower = toLower(remaining);
        
        if (remainingLower.substr(0, 4) == "sqrt" && isWordBoundary(currentExpression, pos + 4)) {
            func = "sqrt";
            isFunction = true;
        } else if (remainingLower.substr(0, 3) == "sin" && isWordBoundary(currentExpression, pos + 3)) {
            func = "sin";
            isFunction = true;
        } else if (remainingLower.substr(0, 3) == "cos" && isWordBoundary(currentExpression, pos + 3)) {
            func = "cos";
            isFunction = true;
        } else if (remainingLower.substr(0, 3) == "tan" && isWordBoundary(currentExpression, pos + 3)) {
            func = "tan";
            isFunction = true;
        } else if (remainingLower.substr(0, 3) == "log" && isWordBoundary(currentExpression, pos + 3)) {
            func = "log";
            isFunction = true;
        } else if (remainingLower.substr(0, 3) == "pow" && isWordBoundary(currentExpression, pos + 3)) {
            func = "pow";
            isFunction = true;
        } else if (remainingLower.substr(0, 3) == "fac" && isWordBoundary(currentExpression, pos + 3)) {
            func = "fac";
            isFunction = true;
        } else if (remainingLower.substr(0, 2) == "ln" && isWordBoundary(currentExpression, pos + 2)) {
            func = "ln";
            isFunction = true;
        }
        
        if (isFunction) {
            pos += func.length();
            skipWhitespace(pos);
            
            if (pos >= (int)currentExpression.length() || currentExpression[pos] != '(') {
                throw ExpressionError("Expected '(' after " + func);
            }
            pos++;
            
            double operand = parseExpression(pos);
            
            skipWhitespace(pos);
            
            if (func == "pow") {
                if (pos >= (int)currentExpression.length() || currentExpression[pos] != ',') {
                    throw ExpressionError("Expected ',' in pow function");
                }
                pos++;
                skipWhitespace(pos);
                
                double exponent = parseExpression(pos);
                
                skipWhitespace(pos);
                if (pos >= (int)currentExpression.length() || currentExpression[pos] != ')') {
                    throw ExpressionError("Expected ')' after exponent");
                }
                pos++;
                
                value = std::pow(operand, exponent);
            } else if (func == "fac") {
                int n = static_cast<int>(operand);
                if (n < 0 || n > 170) {
                    throw ExpressionError("Factorial out of range");
                }
                double result = 1.0;
                for (int i = 2; i <= n; i++) {
                    result *= i;
                }
                value = result;
            } else {
                // All other functions expect ')' after the argument
                if (pos >= (int)currentExpression.length() || currentExpression[pos] != ')') {
                    throw ExpressionError("Expected ')' after function argument");
                }
                pos++;
                
                if (func == "sin") {
                    value = std::sin(operand);
                } else if (func == "sqrt") {
                    if (operand < 0) {
                        throw ExpressionError("Square root of negative number");
                    }
                    value = std::sqrt(operand);
                } else if (func == "cos") {
                    value = std::cos(operand);
                } else if (func == "tan") {
                    value = std::tan(operand);
                } else if (func == "ln") {
                    if (operand <= 0) {
                        throw ExpressionError("Natural logarithm of non-positive number");
                    }
                    value = std::log(operand);
                } else if (func == "log") {
                    if (operand <= 0) {
                        throw ExpressionError("Logarithm base 10 of non-positive number");
                    }
                    value = std::log10(operand);
                }
            }
            hasValue = true;
        }
        
        if (!isFunction) {
            value = parseNumber(pos);
            hasValue = true;
        }
    }
    
    if (!hasValue) {
        throw ExpressionError("Invalid expression");
    }
    
     
    // Check for factorial postfix operator (!)
    skipWhitespace(pos);
    if (pos < (int)currentExpression.length() && currentExpression[pos] == '!') {
        int n = static_cast<int>(value);
        if (n < 0) {
            throw ExpressionError("Factorial of negative number");
        }
        if (n > 170) {
            throw ExpressionError("Factorial out of range");
        }
        double result = 1.0;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        value = result;
        pos++;
        skipWhitespace(pos);
    }
    
    return value;
}

double ExpressionParser::applyUnaryOperator(char op, double value) const {
    if (op == '!') {
        int n = static_cast<int>(value);
        if (n < 0) {
            throw ExpressionError("Factorial of negative number");
        }
        double result = 1.0;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }
    return (op == '-') ? -value : value;
}

} // namespace qwencalc
