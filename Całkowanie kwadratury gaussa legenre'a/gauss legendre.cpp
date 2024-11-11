#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAX_N = 10; // maksymalna liczba węzłów
const int MAX_STOPIEN = 5; // maksymalny stopień wielomianu

// Funkcja do rozwiązania układu równań metodą Gaussa
void gauss(double macierz[MAX_N][MAX_N + 1], double wyniki[MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        // Pivot
        for (int k = i + 1; k < n; k++) {
            if (fabs(macierz[i][i]) < fabs(macierz[k][i])) {
                for (int j = 0; j <= n; j++) {
                    swap(macierz[i][j], macierz[k][j]);
                }
            }
        }

        // Eliminacja
        for (int k = i + 1; k < n; k++) {
            double t = macierz[k][i] / macierz[i][i];
            for (int j = 0; j <= n; j++) {
                macierz[k][j] -= t * macierz[i][j];
            }
        }
    }

    // Back-substitution
    for (int i = n - 1; i >= 0; i--) {
        wyniki[i] = macierz[i][n] / macierz[i][i];
        for (int k = i - 1; k >= 0; k--) {
            macierz[k][n] -= macierz[k][i] * wyniki[i];
        }
    }
}

int main() {
    // Dane aproksymacji
    int stopien = 1; // stopień wielomianu (funkcja liniowa)
    int wezly = 8; // liczba węzłów

    double x_wezly[MAX_N] = {1, 2, 3, 4, 5, 6, 7, 8}; // węzły aproksymacji
    double y_wartosci[MAX_N] = {2, 4, 3, 5, 6, 9, 11, 11}; // wartości funkcji w węzłach
    double wagi[MAX_N] = {1, 1, 1, 1, 1, 1, 1, 1}; // funkcja wagowa (jednolita)

    // Macierz układu równań
    double macierz[MAX_N][MAX_N + 1] = {0};
    double wspolczynniki[MAX_N] = {0}; // współczynniki wielomianu

    // Konstruowanie macierzy układu równań
    for (int i = 0; i <= stopien; i++) {
        for (int j = 0; j <= stopien; j++) {
            for (int k = 0; k < wezly; k++) {
                macierz[i][j] += wagi[k] * pow(x_wezly[k], i + j);
            }
        }
        for (int k = 0; k < wezly; k++) {
            macierz[i][stopien + 1] += wagi[k] * y_wartosci[k] * pow(x_wezly[k], i);
        }
    }

    // Rozwiązanie układu równań metodą Gaussa
    gauss(macierz, wspolczynniki, stopien + 1);

    // Wyświetlenie wyników
    cout << "Liczba węzłów: " << wezly << endl;
    cout << "Współczynniki wielomianu aproksymującego:" << endl;
    for (int i = 0; i <= stopien; i++) {
        cout << "a" << i << " = " << wspolczynniki[i] << endl;
    }

    cout << "Węzły aproksymacji i wartości w węzłach:" << endl;
    for (int i = 0; i < wezly; i++) {
        double y_aproks = 0;
        for (int j = 0; j <= stopien; j++) {
            y_aproks += wspolczynniki[j] * pow(x_wezly[i], j);
        }
        cout << "x = " << x_wezly[i] << ", y = " << y_wartosci[i]
             << ", y_aproks = " << y_aproks << endl;
    }

    return 0;
}
