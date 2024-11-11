#include <iostream>
#include <cmath>

double f(double x) {
    // Definicja funkcji, np. f(x) = cos(x^3 - 2x)
    return cos(x * x * x - 2 * x);
}

void bisection(double a, double b, double epsilon, int max_iter) {
    std::cout << "Równanie: cos(x^3 - 2x) = 0\n";
    int iter = 0;
    double x0;

    while ((b - a) / 2.0 > epsilon && iter < max_iter) {
        x0 = (a + b) / 2.0;
        std::cout << "Iteracja " << iter + 1 << ": x0 = " << x0 << ", f(x0) = " << f(x0) << "\n";

        if (fabs(f(x0)) < epsilon) {
            break;
        }

        if (f(a) * f(x0) < 0) {
            b = x0;
        } else {
            a = x0;
        }

        iter++;
    }

    std::cout << "Pierwiastek w przedziale [" << a << ", " << b << "] wynosi około: " << x0 << "\n";
}

int main() {
    double a = 0.0;
    double b = 2.0;
    double epsilon = 0.01;
    int max_iter = 100;

    bisection(a, b, epsilon, max_iter);

    return 0;
}
