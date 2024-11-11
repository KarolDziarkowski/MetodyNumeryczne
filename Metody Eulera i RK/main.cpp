#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Definiowanie funkcji f(x, y) dla każdego z równań różniczkowych
double f1(double x, double y) {
    return 2 * y * (x + 1);
}

double f2(double x, double y) {
    return x + y;
}

// Metoda Eulera
double euler(double (*f)(double, double), double y0, double x0, double x_end, int N) {
    double h = (x_end - x0) / N;
    double y = y0;
    for (int i = 0; i < N; ++i) {
        y += h * f(x0 + i * h, y);
    }
    return y;
}

// Metoda RK2
double rk2(double (*f)(double, double), double y0, double x0, double x_end, int N) {
    double h = (x_end - x0) / N;
    double y = y0;
    for (int i = 0; i < N; ++i) {
        double k1 = h * f(x0 + i * h, y);
        double k2 = h * f(x0 + (i + 0.5) * h, y + 0.5 * k1);
        y += k2;
    }
    return y;
}

// Metoda RK4
double rk4(double (*f)(double, double), double y0, double x0, double x_end, int N) {
    double h = (x_end - x0) / N;
    double y = y0;
    for (int i = 0; i < N; ++i) {
        double k1 = h * f(x0 + i * h, y);
        double k2 = h * f(x0 + (i + 0.5) * h, y + 0.5 * k1);
        double k3 = h * f(x0 + (i + 0.5) * h, y + 0.5 * k2);
        double k4 = h * f(x0 + (i + 1) * h, y + k3);
        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    }
    return y;
}

int main() {
    double x0 = 0.0;
    double x_end = 1.0;
    int N = 10;
    double h = (x_end - x0) / N;
    // Dla równania y'(x) = 2y(x + 1), y(0) = 1.0
    double y0_1 = 1.0;
    cout << "Równanie: y'(x) = 2y(x + 1), y(0) = 1.0\n";
    cout << "Warunek początkowy: y(" << x0 << ") = " << y0_1 << "\n";
    cout << "Punkt końcowy: x = " << x_end << "\n";
    cout << "Krok obliczeń: N = " << N << "\n";
    cout << "Długość kroku: h = " << h << "\n";
    cout << "Metoda Eulera: y(" << x_end << ") = " << euler(f1, y0_1, x0, x_end, N) << "\n";
    cout << "Metoda RK2: y(" << x_end << ") = " << rk2(f1, y0_1, x0, x_end, N) << "\n";
    cout << "Metoda RK4: y(" << x_end << ") = " << rk4(f1, y0_1, x0, x_end, N) << "\n\n";

    // Dla równania y'(x) = x + y, y(0) = 0.1
    double y0_2 = 0.1;
    cout << "Równanie: y'(x) = x + y, y(0) = 0.1\n";
    cout << "Warunek początkowy: y(" << x0 << ") = " << y0_2 << "\n";
    cout << "Punkt końcowy: x = " << x_end << "\n";
    cout << "Krok obliczeń: N = " << N << "\n";
    cout << "Długość kroku: h = " << h << "\n";
    cout << "Metoda Eulera: y(" << x_end << ") = " << euler(f2, y0_2, x0, x_end, N) << "\n";
    cout << "Metoda RK2: y(" << x_end << ") = " << rk2(f2, y0_2, x0, x_end, N) << "\n";
    cout << "Metoda RK4: y(" << x_end << ") = " << rk4(f2, y0_2, x0, x_end, N) << "\n";

    return 0;
}
