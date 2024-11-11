#include <iostream>
#include <fstream>

using namespace std;

void czytajDaneZPliku(const string& nazwaPliku, double*& wartosci_x, double*& wartosci_y, int& liczba_punktow) {
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        cerr << "Nie udalo sie otworzyc pliku: " << nazwaPliku << endl;
        return;
    }

    plik >> liczba_punktow;

    wartosci_x = new double[liczba_punktow];
    wartosci_y = new double[liczba_punktow];

    for (int i = 0; i < liczba_punktow; ++i) {
        plik >> wartosci_x[i] >> wartosci_y[i];
    }

    plik.close();
}

void obliczWspolczynniki(double* wartosci_x, double* wartosci_y, double*& wspolczynniki_b, int liczba_punktow) {
    wspolczynniki_b = new double[liczba_punktow];
    for (int i = 0; i < liczba_punktow; ++i) {
        wspolczynniki_b[i] = wartosci_y[i];
    }

    for (int j = 1; j < liczba_punktow; ++j) {
        for (int i = liczba_punktow - 1; i >= j; --i) {
            wspolczynniki_b[i] = (wspolczynniki_b[i] - wspolczynniki_b[i - 1]) / (wartosci_x[i] - wartosci_x[i - j]);
        }
    }
}

double interpoluj(double x, double* wartosci_x, double* wspolczynniki_b, int liczba_punktow) {
    double wynik = wspolczynniki_b[0];
    double temp = 1.0;

    for (int i = 1; i < liczba_punktow; ++i) {
        temp *= (x - wartosci_x[i - 1]);
        wynik += wspolczynniki_b[i] * temp;
    }

    return wynik;
}

void wypiszWynik(double x, double* wartosci_x, double* wartosci_y, double* wspolczynniki_b, int liczba_punktow) {
    cout << "Liczba wezlow: " << liczba_punktow << endl;
    cout << "Dane: Wzory interpolacyjne i wartosci funkcji w wezlach:" << endl;
    for (int i = 0; i < liczba_punktow; ++i) {
        cout << "x" << i << ": " << wartosci_x[i] << "\ty" << i << ": " << wartosci_y[i] << endl;
    }
    cout << "Punkt, w ktorym liczymy wartosc wielomianu: " << x << endl;
    cout << "Wartosc wielomianu Newtona w danym punkcie: " << interpoluj(x, wartosci_x, wspolczynniki_b, liczba_punktow) << endl;
    cout << "Wspolczynniki wielomianu Newtona (b_k): ";
    for (int i = 0; i < liczba_punktow; ++i) {
        cout << "b" << i << ": " << wspolczynniki_b[i] << " ";
    }
    cout << endl;
}

int main() {
    double* wartosci_x = nullptr;
    double* wartosci_y = nullptr;
    double* wspolczynniki_b = nullptr;
    int liczba_punktow = 0;

    czytajDaneZPliku("dane1.txt", wartosci_x, wartosci_y, liczba_punktow);
    obliczWspolczynniki(wartosci_x, wartosci_y, wspolczynniki_b, liczba_punktow);

    double x1 = 5.0;
    double x2 = 10.0;

    wypiszWynik(x1, wartosci_x, wartosci_y, wspolczynniki_b, liczba_punktow);
    wypiszWynik(x2, wartosci_x, wartosci_y, wspolczynniki_b, liczba_punktow);

    // Zwolnienie zaalokowanej pamięci
    delete[] wartosci_x;
    delete[] wartosci_y;
    delete[] wspolczynniki_b;

    return 0;
}
