#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int MAX_ROZMIAR = 20;

void wczytajMacierzZPliku(double A[MAX_ROZMIAR][MAX_ROZMIAR], double B[MAX_ROZMIAR], int& n, string nazwaPliku) {
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        cout << "Nie mogę otworzyć pliku " << nazwaPliku << endl;
        exit(1);
    }

    plik >> n;
    if (n < 1 || n > MAX_ROZMIAR) {
        cout << "Zły rozmiar macierzy." << endl;
        exit(1);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            plik >> A[i][j];
        }
        plik >> B[i];
    }
    plik.close();
}

void wypiszMacierz(double macierz[MAX_ROZMIAR][MAX_ROZMIAR], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << macierz[i][j] << "\t";
        }
        cout << endl;
    }
}

bool sprawdzDominacjeDiagonalna(double A[MAX_ROZMIAR][MAX_ROZMIAR], int n) {
    int licznik = 0;
    for (int i = 0; i < n; ++i) {
        double wartoscDiagonalna = abs(A[i][i]);
        double suma = 0.0;
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                suma += abs(A[i][j]);
            }
        }
        if (wartoscDiagonalna < suma) {
            return false;
        }
        else if (wartoscDiagonalna > suma)
        {
            licznik++;
        }

    }
    if (licznik)
    {
        return true;
    }
    return false;
}

void rozlozMacierz(double A[MAX_ROZMIAR][MAX_ROZMIAR], double L[MAX_ROZMIAR][MAX_ROZMIAR], double U[MAX_ROZMIAR][MAX_ROZMIAR], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if  (i < j) {
                U[i][j] = A[i][j];
                L[i][j] = 0.0;
            }
             else if (i>j) {
                L[i][j] = A[i][j];
                U[i][j] = 0.0;
            }
            else
            {
                U[i][j] = 0;
                L[i][j] = 0;
            }
        }
    }
}

void wypiszDiagonalnaOdwracalna(double D_odw[MAX_ROZMIAR][MAX_ROZMIAR], int n) {
    cout << "Macierz D^-1:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                cout << D_odw[i][j] << "\t";
            }
            else {
                cout << "0\t";
            }
        }
        cout << endl;
    }
}

void rozwiazJacobi(double A[MAX_ROZMIAR][MAX_ROZMIAR], double B[MAX_ROZMIAR], int n, int max_iteracji, double epsilon) {
    double x[MAX_ROZMIAR] = { 0 };
    double x_nowe[MAX_ROZMIAR];

    
    for (int iter = 0; iter < max_iteracji; ++iter) {
        for (int i = 0; i < n; ++i) {
            double suma = 0.0;
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    suma += A[i][j] * x[j];
                }
            }
            x_nowe[i] = (B[i] - suma) / A[i][i]; //Wykorzystujanie aktualnej wartości x do obliczenia nowej wartości.
        }

        //Obliczanie maksymalnego błędu między nowym x a poprzednim x, aby sprawdzić, czy algorytm zbiega.
        double max_blad = 0.0;
        for (int i = 0; i < n; ++i) {
            double blad = abs(x_nowe[i] - x[i]);
            if (blad > max_blad) {
                max_blad = blad;
            }
            x[i] = x_nowe[i]; 
        }

       
        cout << "Iteracja " << iter + 1 << ": ";
        for (int i = 0; i < n; ++i) {
            cout << "x[" << i << "]= " << x[i] << " ";
        }
        cout << " Max błąd: " << max_blad << endl;

        if (max_blad < epsilon) {
            cout << "Zbieżne z epsilonem = " << epsilon << " po " << iter + 1 << " iteracjach." << endl;
            break;
        }  //Sprawdzanie czy algorytm zbiegł do rozwiązania z zadaną dokładnością epsilon
    }
}

void dodajLU(double L[MAX_ROZMIAR][MAX_ROZMIAR], double U[MAX_ROZMIAR][MAX_ROZMIAR], double LU[MAX_ROZMIAR][MAX_ROZMIAR], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            LU[i][j] = L[i][j] + U[i][j];
        }
    }
}

int main() {
    double A[MAX_ROZMIAR][MAX_ROZMIAR];
    double B[MAX_ROZMIAR];
    double L[MAX_ROZMIAR][MAX_ROZMIAR];
    double U[MAX_ROZMIAR][MAX_ROZMIAR];
    double D_odw[MAX_ROZMIAR][MAX_ROZMIAR];
    int n, max_iteracji;

    
    string nazwaPliku = "plik.txt";
    wczytajMacierzZPliku(A, B, n, nazwaPliku);

    
    if (!sprawdzDominacjeDiagonalna(A, n)) {
        cout << "Macierz nie jest diagonalnie dominująca." << endl;
        return 1;
    }

    rozlozMacierz(A, L, U, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                D_odw[i][j] = 1.0 / A[i][j];
            }
            else {
                D_odw[i][j] = 0.0;
            }
        }
    }
  
    double LU[MAX_ROZMIAR][MAX_ROZMIAR];
    dodajLU(L, U, LU, n);

  
    cout << "Macierz L + U:" << endl;
    wypiszMacierz(LU, n);

    wypiszDiagonalnaOdwracalna(D_odw, n);

    cout << "Podaj maksymalną liczbę iteracji: ";
    cin >> max_iteracji;

    
    double epsilon_1 = 0.001;
    cout << "\nRozwiązanie z epsilonem  = " << epsilon_1 << endl;
    rozwiazJacobi(A, B, n, max_iteracji, epsilon_1);

    double epsilon_2 = 0.000001;
    cout << "\nRozwiązanie z epsilonem = " << epsilon_2 << endl;
    rozwiazJacobi(A, B, n, max_iteracji, epsilon_2);

    return 0;
}
