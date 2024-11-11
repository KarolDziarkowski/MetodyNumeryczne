#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Funkcja f1(x) i jej pochodna f1'(x)
double funkcja1(double x) {
    return x * x * x - 6 * x * x + 11 * x - 6;
}

double pochodna_funkcji1(double x) {
    return 3 * x * x - 12 * x + 11;
}

// Funkcja f2(x) i jej pochodna f2'(x)
double funkcja2(double x) {
    return x * x * x * x - 4 * x * x * x + 6 * x * x - 4 * x + 1;
}

double pochodna_funkcji2(double x) {
    return 4 * x * x * x - 12 * x * x + 12 * x - 4;
}

// Metoda Newtona (stycznych)
void metoda_stycznych(double (*f)(double), double (*f_pochodna)(double), double x0, double epsilon) {
    cout << "Metoda stycznych (Newtona):" << endl;
    int iteracja = 0;
    while (true) {
        double fx = f(x0);
        double fpx = f_pochodna(x0);
        if (fabs(fpx) < epsilon) {
            cout << "Pochodna jest zbyt mała, metoda może nie zbiegać." << endl;
            return;
        }
        double x1 = x0 - fx / fpx;
        cout << "Iteracja " << ++iteracja << ": x = " << x1 << ", f(x) = " << f(x1) << endl;
        if (fabs(f(x1)) < epsilon) {
            cout << "Rozwiązanie znalezione: x = " << x1 << ", f(x) = " << f(x1) << endl;
            return;
        }
        x0 = x1;
    }
}

// Metoda siecznych
void metoda_siecznych(double (*f)(double), double x0, double epsilon) {
    cout << "Metoda siecznych:" << endl;
    double x1 = x0 - 0.1;
    int iteracja = 0;
    while (true) {
        double fx0 = f(x0);
        double fx1 = f(x1);
        if (fabs(fx1 - fx0) < epsilon) {
            cout << "Różnica w wartościach funkcji jest zbyt mała, metoda może nie zbiegać." << endl;
            return;
        }
        double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        cout << "Iteracja " << ++iteracja << ": x = " << x2 << ", f(x) = " << f(x2) << endl;
        if (fabs(f(x2)) < epsilon) {
            cout << "Rozwiązanie znalezione: x = " << x2 << ", f(x) = " << f(x2) << endl;
            return;
        }
        x0 = x1;
        x1 = x2;
    }
}

int main() {
    double punkt_startowy;
    double epsilon;

    cout << "Podaj punkt startowy x0: ";
    cin >> punkt_startowy;
    cout << "Podaj dokładność epsilon: ";
    cin >> epsilon;

    cout << "Rozwiązywanie dla funkcji 1: f(x) = x^3 - 6x^2 + 11x - 6" << endl;
    metoda_stycznych(funkcja1, pochodna_funkcji1, punkt_startowy, epsilon);
    metoda_siecznych(funkcja1, punkt_startowy, epsilon);

    cout << "\nRozwiązywanie dla funkcji 2: f(x) = x^4 - 4x^3 + 6x^2 - 4x + 1" << endl;
    metoda_stycznych(funkcja2, pochodna_funkcji2, punkt_startowy, epsilon);
    metoda_siecznych(funkcja2, punkt_startowy, epsilon);

    return 0;
}
