#include "ExpressionParser.h"
#include <cmath>
#include <cctype>
#include <string>

namespace qwencalc {

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
        
        if (c == '*' || c == '/' || c == '%') {
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
            }
        } else {
            break;
        }
    }
    
    return left;
}

double ExpressionParser::parseNumber(int& pos) const {
    skipWhitespace(pos);
    
    // Check for mathematical constants
    if (pos + 2 <= (int)currentExpression.length()) {
        std::string substr = currentExpression.substr(pos, 2);
        if (substr == "PI" || substr == "pi" || substr == "Pi" || substr == "pI") {
            pos += 2;
            return M_PI;
        }
    }
    if (pos + 4 <= (int)currentExpression.length()) {
        std::string substr = currentExpression.substr(pos, 4);
        if (substr == "M_PI" || substr == "m_pi" || substr == "mPi" || substr == "MpI") {
            pos += 4;
            return M_PI;
        }
    }
    if (currentExpression[pos] == 'e' || currentExpression[pos] == 'E') {
        pos++;
        return M_E;
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
            for (int i = 0; i < std::abs(exponentValue); i++) {
                if (exponentValue >= 0) {
                    exponent *= 10.0;
                } else {
                    exponent /= 10.0;
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
    
    double value;
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
        value = parseNumber(pos);
        if (signCount % 2 == 1) {
            value = -value;
        }
        hasValue = true;
    } else {
        // Check for function name
        std::string func = "";
        bool isFunction = false;
        
        if (currentExpression[pos] == 's' || currentExpression[pos] == 'S') {
            if (pos + 3 <= (int)currentExpression.length()) {
                std::string substr = currentExpression.substr(pos, 3);
                if (substr == "sin" || substr == "SIN" || substr == "Sin" || substr == "sIn" || substr == "siN") {
                    func = "sin";
                    isFunction = true;
                } else if (substr == "sqr" || substr == "SQR" || substr == "Sqr" || substr == "sQr" || substr == "SqR") {
                    func = "sqrt";
                    isFunction = true;
                }
            }
        } else if (currentExpression[pos] == 'x' || currentExpression[pos] == 'X') {
            if (pos + 3 <= (int)currentExpression.length()) {
                std::string substr = currentExpression.substr(pos, 3);
                if (substr == "sqrt" || substr == "SQRT" || substr == "Sqrt" || substr == "sQrt" || substr == "SqRt" || substr == "SqRT") {
                    func = "sqrt";
                    isFunction = true;
                }
            }
        } else if (currentExpression[pos] == 'c' || currentExpression[pos] == 'C') {
            if (pos + 3 <= (int)currentExpression.length()) {
                std::string substr = currentExpression.substr(pos, 3);
                if (substr == "cos" || substr == "COS" || substr == "Cos" || substr == "cOs" || substr == "CoS") {
                    func = "cos";
                    isFunction = true;
                }
            }
        } else if (currentExpression[pos] == 't' || currentExpression[pos] == 'T') {
            if (pos + 3 <= (int)currentExpression.length()) {
                std::string substr = currentExpression.substr(pos, 3);
                if (substr == "tan" || substr == "TAN" || substr == "Tan" || substr == "tAn" || substr == "TaN") {
                    func = "tan";
                    isFunction = true;
                }
            }
        } else if (currentExpression[pos] == 'l' || currentExpression[pos] == 'L') {
            if (pos + 2 <= (int)currentExpression.length()) {
                std::string substr = currentExpression.substr(pos, 2);
                if (substr == "ln" || substr == "LN" || substr == "Ln" || substr == "lN") {
                    func = "ln";
                    isFunction = true;
                } else if (pos + 3 <= (int)currentExpression.length()) {
                    std::string substr3 = currentExpression.substr(pos, 3);
                    if (substr3 == "log" || substr3 == "LOG" || substr3 == "Log" || substr3 == "lOG" || substr3 == "LoG" || substr3 == "loG") {
                        func = "log";
                        isFunction = true;
                    }
                }
            }
        } else if (currentExpression[pos] == 'n' || currentExpression[pos] == 'N') {
            if (pos + 2 <= (int)currentExpression.length()) {
                std::string substr = currentExpression.substr(pos, 2);
                if (substr == "ln" || substr == "LN" || substr == "Ln" || substr == "lN") {
                    func = "ln";
                    isFunction = true;
                }
            }
        } else if (currentExpression[pos] == 'p' || currentExpression[pos] == 'P') {
            if (pos + 3 <= (int)currentExpression.length()) {
                std::string substr = currentExpression.substr(pos, 3);
                if (substr == "pow" || substr == "POW" || substr == "Pow" || substr == "pOW" || substr == "PoW" || substr == "POw" || substr == "PoW") {
                    func = "pow";
                    isFunction = true;
                }
            }
        } else if (currentExpression[pos] == 'f' || currentExpression[pos] == 'F') {
            if (pos + 3 <= (int)currentExpression.length()) {
                std::string substr = currentExpression.substr(pos, 3);
                if (substr == "fac" || substr == "FAC" || substr == "Fac" || substr == "fAc" || substr == "FaC") {
                    func = "fac";
                    isFunction = true;
                }
            }
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
