#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 20;


void wczytaj_macierz(const string& nazwa_pliku, double A[][MAX_SIZE], int& n) {
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


void wypisz_macierz(double A[][MAX_SIZE], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(12) << A[i][j];
        }
        cout << endl;
    }
}


void wypisz_wektor(double B[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << setw(12) << B[i];
    }
    cout << endl;
}


void rozwiaz_uklad(double A[][MAX_SIZE], double B[], int n) {
    double L[MAX_SIZE][MAX_SIZE] = {0};
    double U[MAX_SIZE][MAX_SIZE] = {0};


    for (int i = 0; i < n; ++i) {

        for (int k = i; k < n; ++k) {
            double sum = 0;
            for (int j = 0; j < i; ++j) {
                sum += (L[i][j] * U[j][k]);
            }
            U[i][k] = A[i][k] - sum;
        }


        for (int k = i; k < n; ++k) {
            if (i == k) {
                L[i][i] = 1; 
            } else {
                double sum = 0;
                for (int j = 0; j < i; ++j) {
                    sum += (L[k][j] * U[j][i]);
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }


    for (int i = 0; i < n; ++i) {
        if (U[i][i] == 0) {
            cerr << "Błąd: Zero na przekątnej macierzy." << endl;
            exit(1);
        }
    }

  
    cout << "Macierz L:" << endl;
    wypisz_macierz(L, n);
    cout << endl;

    cout << "Macierz U:" << endl;
    wypisz_macierz(U, n);
    cout << endl;


    double Y[MAX_SIZE] = {0};
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < i; ++j) {
            sum += L[i][j] * Y[j];
        }
        Y[i] = (B[i] - sum) / L[i][i];
    }


    cout << "Wektor Y:" << endl;
    wypisz_wektor(Y, n);
    cout << endl;


    double X[MAX_SIZE] = {0};
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j) {
            sum += U[i][j] * X[j];
        }
        X[i] = (Y[i] - sum) / U[i][i];
    }


    cout << "Rozwiązanie układu równań (x0 - xn):" << endl;
    wypisz_wektor(X, n);
}

int main() {
    const int MAX_SIZE = 20;
    int n = 20;

    


    double A[MAX_SIZE][MAX_SIZE]; 
    double B[MAX_SIZE];           


    wczytaj_macierz("A2.txt", A, n);
    wczytaj_wektor("B2.txt", B, n);


    cout << "Macierz rozszerzona przed obliczeniami:" << endl;
    wypisz_macierz(A, n);
    cout << endl;


    rozwiaz_uklad(A, B, n);

    return 0;
}