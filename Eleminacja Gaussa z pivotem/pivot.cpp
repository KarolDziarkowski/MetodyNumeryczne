#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>  // Dodane dla funkcji abs()

using namespace std;

// Funkcja do wczytywania macierzy z pliku
void wczytaj_macierz(const string& nazwa_pliku, double A[][20], int n) {
    ifstream plik(nazwa_pliku);
    double wartosc;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (plik >> wartosc) {
                A[i][j] = wartosc;
            } else {
                cerr << "Błąd podczas wczytywania danych z pliku." << endl;
                exit(1);
            }
        }
    }
}

// Funkcja do wczytywania wektora z pliku
void wczytaj_wektor(const string& nazwa_pliku, double B[], int n) {
    ifstream plik(nazwa_pliku);
    double wartosc;

    for (int i = 0; i < n; ++i) {
        if (plik >> wartosc) {
            B[i] = wartosc;
        } else {
            cerr << "Błąd podczas wczytywania danych z pliku." << endl;
            exit(1);
        }
    }
}

// Funkcja do wypisywania macierzy
void wypisz_macierz(double A[][20], double B[], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(12) << A[i][j];
        }
        cout << setw(5) << "|" << setw(12) << B[i] << endl;
    }
}

// Funkcja do zamiany wierszy
void zamien_wiersze(double A[][20], double B[], int w1, int w2, int n) {
    for (int i = 0; i < n; ++i) {
        swap(A[w1][i], A[w2][i]);
    }
    swap(B[w1], B[w2]);
}

// Funkcja do eliminacji Gaussa z częściowym wyborem pivota
void eliminacja_gaussa(double A[][20], double B[], int n) {
    // Eliminacja współczynników
    for (int i = 0; i < n; ++i) {
        // Częściowy wybór pivota
        int max_index = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(A[k][i]) > abs(A[max_index][i])) {
                max_index = k;
            }
        }
        if (max_index != i) {
            zamien_wiersze(A, B, i, max_index, n);
        }

        if (A[i][i] == 0) {
            cerr << "Błąd: Zero na przekątnej macierzy." << endl;
            exit(1);
        }

        for (int k = i + 1; k < n; ++k) {
            double stosunek = A[k][i] / A[i][i];
            for (int j = i; j < n; ++j) {
                A[k][j] -= stosunek * A[i][j];
            }
            B[k] -= stosunek * B[i];
        }
    }

    // Obliczanie rozwiązań
    double X[n];
    for (int i = n - 1; i >= 0; --i) {
        X[i] = B[i];
        for (int j = i + 1; j < n; ++j) {
            X[i] -= A[i][j] * X[j];
        }
        X[i] /= A[i][i];
    }

    // Wypisywanie rozwiązania
    cout << "Rozwiązanie układu równań (x0 - xn):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "x" << i << ": " << X[i] << endl;
    }
}

int main() {
    const int n = 20;  // Rozmiar macierzy

    double A[n][20];  // Macierz współczynników
    double B[n];      // Wektor prawych stron

    // Wczytywanie danych
    wczytaj_macierz("A2.txt", A, n);
    wczytaj_wektor("B2.txt", B, n);

    // Wypisywanie macierzy rozszerzonej przed obliczeniami
    cout << "Macierz rozszerzona przed obliczeniami:" << endl;
    wypisz_macierz(A, B, n);
    cout << endl;

    // Wywołanie funkcji eliminacji Gaussa
    eliminacja_gaussa(A, B, n);

    return 0;
}
