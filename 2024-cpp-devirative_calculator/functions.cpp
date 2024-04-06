#include "functions.h"
// Function that returns the power of a number
double pow(double base, int exponent)
{
    double result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

// Function that can give us the number's sign
double sign(double x)
{
    if (x > 0) {
        return 1;
    }
    else if (x < 0) {
        return -1;
    }
    else {
        return 0;
    }
}

