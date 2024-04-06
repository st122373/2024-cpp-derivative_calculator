#include <iostream>
#include <cmath>
#include <string>

double eval(const char* expr) {
    double value = 0.0;
    sscanf_s(expr, "%lf", &value);
    return value;
}

int main() {
    std::string expression;

    std::cout << "Enter the evaluation ";
    std::getline(std::cin, expression);

    const char* expr = expression.c_str();

    double result = eval(expr);

    std::cout << "result: " << result << std::endl;

    return 0;
}
