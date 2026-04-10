#include "backend/CalculatorEngine.h"
#include <iostream>

int main() {
    qwencalc::CalculatorEngine engine;
    double result = engine.calculate("2 + 2");
    std::cout << "Result: " << result << std::endl;
    return 0;
}
