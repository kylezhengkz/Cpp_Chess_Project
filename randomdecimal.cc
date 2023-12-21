#include "randomdecimal.h"
double RandomDecimal::generateRandomDecimal() {
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<double> dist(0.0, 1.0);
    double randNum = dist(gen);

    double result = 0.001 / (1.0 - randNum);
    return result;
}
