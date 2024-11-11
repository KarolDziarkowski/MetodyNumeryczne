#include <iostream>
#include <cmath>

using namespace std;

// Definicje funkcji podcałkowych
double funkcja1(double x) {
    return sin(x);
}

double funkcja2(double x) {
    return x*x + 2*x + 5;
}

double funkcja3(double x) {
    return exp(x);
}

// Funkcja obliczająca całkę metodą prostokątów
double calka_prostokatow(double (*funkcja)(double), double a, double b, int n) {
    double dx = (b - a) / n;
    double calka = 0;
    for (int i = 0; i < n; i++) {
        calka += funkcja(a + i * dx);
    }
    return calka * dx;
}

// Funkcja obliczająca całkę metodą trapezów
double calka_trapezow(double (*funkcja)(double), double a, double b, int n) {
    double dx = (b - a) / n;
    double calka = 0.5 * (funkcja(a) + funkcja(b));
    for (int i = 1; i < n; i++) {
        calka += funkcja(a + i * dx);
    }
    return calka * dx;
}

// Funkcja obliczająca całkę metodą parabol
double calka_parabol(double (*funkcja)(double), double a, double b, int n) {
    double dx = (b - a) / n;
    double calka = funkcja(a) + funkcja(b);
    for (int i = 1; i < n; i++) {
        double x = a + i * dx;
        calka += (i % 2 == 0 ? 2 : 4) * funkcja(x);
    }
    return calka * dx / 3;
}



int main() {
    double a = 0.5;
    double b = 2.5;
    int n = 4;

    cout << "Funkcja 1: sin(x), przedział [" << a << ", " << b << "], liczba przedziałów: " << n << endl;
    cout << "Metoda prostokątów: " << calka_prostokatow(funkcja1, a, b, n) << endl;
    cout << "Metoda trapezów: " << calka_trapezow(funkcja1, a, b, n) << endl;
    cout << "Metoda parabol: " << calka_parabol(funkcja1, a, b, n) << endl;

    a = 0.5;
    b = 5;
    cout << "\nFunkcja 2: x^2 + 2x + 5, przedział [" << a << ", " << b << "], liczba przedziałów: " << n << endl;
    cout << "Metoda prostokątów: " << calka_prostokatow(funkcja2, a, b, n) << endl;
    cout << "Metoda trapezów: " << calka_trapezow(funkcja2, a, b, n) << endl;
    cout << "Metoda parabol: " << calka_parabol(funkcja2, a, b, n) << endl;

    a = 0.5;
    b = 5;
    cout << "\nFunkcja 3: e^x, przedział [" << a << ", " << b << "], liczba przedziałów: " << n << endl;
    cout << "Metoda prostokątów: " << calka_prostokatow(funkcja3, a, b, n) << endl;
    cout << "Metoda trapezów: " << calka_trapezow(funkcja3, a, b, n) << endl;
    cout << "Metoda parabol: " << calka_parabol(funkcja3, a, b, n) << endl;

    return 0;
}
