#include <iostream>
#include <cmath>

double f(double x) {
    // Definicja funkcji, np. f(x) = cos(x^3 - 2x)
    return cos(x * x * x - 2 * x);
}

void regula_falsi(double a, double b, double epsilon, int max_iter) {
    std::cout << "Równanie: cos(x^3 - 2x) = 0\n";
    int iter = 0;
    double x1;

    while (iter < max_iter) {
        x1 = a - (f(a) * (b - a)) / (f(b) - f(a));
        std::cout << "Iteracja " << iter + 1 << ": x1 = " << x1 << ", f(x1) = " << f(x1) << "\n";

        if (fabs(f(x1)) < epsilon) {
            break;
        }

        if (f(x1) * f(a) < 0) {
            b = x1;
        } else {
            a = x1;
        }

        iter++;
    }

    std::cout << "Pierwiastek w przedziale [" << a << ", " << b << "] wynosi około: " << x1 << "\n";
}

int main() {
    double a = 0.0;
    double b = 2.0;
    double epsilon = 0.01;
    int max_iter = 100;

    regula_falsi(a, b, epsilon, max_iter);

    return 0;
}

